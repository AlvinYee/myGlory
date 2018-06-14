import sys

sys.path.append('../')
sys.path.append('../../')
from xml.dom.minidom import parse
from PkCocoCfgValidator.MdCocoCfgValidator import CocoCfgValidator


class CocoConfigurator(object):

    def __init__(self, mq_xml):
        try:
            self.xmlDoc = parse(mq_xml)
        except IOError:
            print('input/output set up incorrectly')
        print('[INFO]: validating xml starts')
        CocoCfgValidator(self.xmlDoc)
        print('[INFO]: validating xml ends')

    def generate_hfile(self, hfile):
        max_signal_num = 0
        with open(hfile, 'w') as hFile:
            hFile.write('#ifndef COCO_CFG_H_\n')
            hFile.write('#define COCO_CFG_H_\n\n')
            hFile.write('#include "mq_type.h"\n\n')

            # create parameter macro
            hFile.write('/***** generate parameter macro *****/\n')
            for parameter in (self.xmlDoc.getElementsByTagName('Parameters')[0].getElementsByTagName('Parameter')):
                hFile.write(
                    '#define {0} {1}\n'.format(parameter.getElementsByTagName('predefinedPar')[0].firstChild.nodeValue,
                                               parameter.getElementsByTagName('actualValue')[0].firstChild.nodeValue))

            # iterate each msg, simply create the macro for each configuration item
            for index, msg in enumerate(self.xmlDoc.getElementsByTagName('I2CMsg')):
                hFile.write('/***** generate msg configuration item macro *****/\n')
                # find th max signal num by iterating each msg
                max_signal_num = max(max_signal_num, len(msg.getElementsByTagName('signal')))
                # iterate each element under each msg
                for msg_element in msg.childNodes:
                    if msg_element.nodeName == 'predefinedMsg':
                        msg_name = msg_element.firstChild.nodeValue
                        # define msg index
                        hFile.write('#define {0}_idx {1}\n'.format(msg_name, index))
                    if msg_element.nodeName not in ('#text', 'signals'):
                        hFile.write('#define {0}_{1}_cfg    {2}\n'.format(msg_name, msg_element.nodeName,
                                                                          msg_element.firstChild.nodeValue))
                # iterate each signal under signals under each msg
                hFile.write('/***** generate signal configuration item macro *****/\n')
                for idx, signal in enumerate(msg.getElementsByTagName('signals')[0].getElementsByTagName('signal')):
                    for signal_element in signal.childNodes:
                        if signal_element.nodeName == 'predefinedSig':
                            signal_name = signal_element.firstChild.nodeValue
                            # define signal index
                            hFile.write('#define {0}_idx {1}\n'.format(signal_name, idx))
                        if signal_element.nodeName != '#text':
                            hFile.write('#define {0}_{1}_cfg    {2}\n'.format(signal_name, signal_element.nodeName,
                                                                              signal_element.firstChild.nodeValue))
            hFile.write('#define msgNum {0}\n'.format(index + 1))

            # create signal data structure definition
            hFile.write('/***** generate signal config structure *****/\n')
            hFile.write('typedef struct{\n')
            for msg in self.xmlDoc.getElementsByTagName('I2CMsg'):
                for signal in msg.getElementsByTagName('signals')[0].getElementsByTagName('signal'):
                    for signal_element in signal.childNodes:
                        if signal_element.nodeName not in ('#text', 'predefinedSig', 'defaultValue'):
                            hFile.write('\t{0} const {1};\n'.format(signal_element.getAttribute("dataType"),
                                                                    signal_element.nodeName))
                    break
                break
            hFile.write('}SIGNAL_CONFIG_Tag;\n')

            # create msg data structure definition
            hFile.write('/***** generate msg config structure *****/\n')
            hFile.write('typedef struct{\n')
            for msg in self.xmlDoc.getElementsByTagName('I2CMsg'):
                for msg_element in msg.childNodes:
                    if msg_element.nodeName not in ('#text', 'signals', 'predefinedMsg'):
                        hFile.write(
                            '\t{0} const {1};\n'.format(msg_element.getAttribute("dataType"), msg_element.nodeName))
                break
            hFile.write('\tSIGNAL_CONFIG_Tag signalConfig[{0}];\n'.format(max_signal_num))
            hFile.write('}MSG_CONFIG_Tag;\n')
            hFile.write('extern const MSG_CONFIG_Tag CocoConfigurations[];\n\n')

            # create external declaration of variables that hold signal
            for signal in self.xmlDoc.getElementsByTagName("signal"):
                for signalEnable in signal.getElementsByTagName('sigEnable'):
                    if signalEnable.firstChild.nodeValue == "TRUE":
                        for actualSig in signal.getElementsByTagName('actualSig'):
                            if actualSig.firstChild.nodeValue != "NUL":
                                hFile.write(
                                    'extern {0} {1};\n'.format(actualSig.getAttribute('dataType').strip('*'),
                                                               actualSig.firstChild.nodeValue))
                            else:
                                raise AttributeError(
                                    'signal {0} enabled but not mapped to a real signal'.format(
                                        signal.getElementsByTagName('predefinedSig')[0].firstChild.nodeValue))
            hFile.write('#endif /* COCO_CFG_H_ */\n\n')

    def generate_cfile(self, cfile):
        with open(cfile, 'w') as cFile:
            cFile.write('#include "CocoCfg.h"\n')
            cFile.write('#include "I2CCAN_Par.h"\n')
            cFile.write('#include "APP_SDA.h"\n')
            cFile.write('const MSG_CONFIG_Tag CocoConfigurations[] = \n')
            # level 1
            cFile.write('{\n')

            # create the entity of msg element in the configuration table
            for msg in self.xmlDoc.getElementsByTagName('I2CMsg'):
                # level 2
                cFile.write('\t{\n')
                for msg_element in msg.childNodes:
                    if msg_element.nodeName != '#text' and msg_element.nodeName != 'signals':
                        # level 3
                        if msg_element.nodeName == 'predefinedMsg':
                            pass
                        elif msg_element.getAttribute("dataType").endswith(
                                '*') and msg_element.firstChild.nodeValue != "NUL":
                            cFile.write('\t\t({3})(&{0}),//{1} {2}\n'.format(msg_element.firstChild.nodeValue,
                                                                             msg_element.getAttribute("dataType"),
                                                                             msg_element.nodeName,
                                                                             msg_element.getAttribute("dataType")))
                        else:
                            cFile.write('\t\t{0},//{1} {2}\n'.format(msg_element.firstChild.nodeValue,
                                                                     msg_element.getAttribute("dataType"),
                                                                     msg_element.nodeName))
                # level 3
                cFile.write('\t\t{\n')

                # create the entity of signal element in the configuration table
                for signal in msg.getElementsByTagName('signals')[0].getElementsByTagName('signal'):
                    # level 4
                    cFile.write('\t\t\t{\n')
                    for signal_element in signal.childNodes:
                        if signal_element.nodeName != '#text':
                            # level 5
                            if signal_element.nodeName in ('predefinedSig', 'defaultValue'):
                                pass
                            elif signal_element.getAttribute("dataType").endswith(
                                    '*') and signal_element.firstChild.nodeValue != 'NUL':
                                cFile.write(
                                    '\t\t\t\t&{0},//{1} {2}\n'.format(signal_element.firstChild.nodeValue,
                                                                      signal_element.getAttribute(
                                                                          "dataType"),
                                                                      signal_element.nodeName))
                            else:
                                cFile.write('\t\t\t\t{0},//{1} {2}\n'.format(signal_element.firstChild.nodeValue,
                                                                             signal_element.getAttribute("dataType"),
                                                                             signal_element.nodeName))
                    # level 4
                    cFile.write('\t\t\t},\n')
                # level 3
                cFile.write('\t\t}\n')
                # level 2
                cFile.write('\t},\n')
            # level 1
            cFile.write('};\n')

            # create definition of variables that hold signal
            for signal in self.xmlDoc.getElementsByTagName("signal"):
                for signalEnable in signal.getElementsByTagName('sigEnable'):
                    if signalEnable.firstChild.nodeValue == "TRUE":
                        for actualSig in signal.getElementsByTagName('actualSig'):
                            if actualSig.firstChild.nodeValue != "NUL":
                                cFile.write('{0} {1};\n'.format(actualSig.getAttribute('dataType').strip('*'),
                                                                actualSig.firstChild.nodeValue))
                            else:
                                raise AttributeError(
                                    'signal {0} enabled but not mapped to a real signal'.format(
                                        signal.getElementsByTagName('predefinedSig')[0].firstChild.nodeValue))

    def generate_signal_updating(self, msg_name):
        s = ''
        for msg in self.xmlDoc.getElementsByTagName('I2CMsg'):
            if msg.getElementsByTagName('predefinedMsg')[0].firstChild.nodeValue == msg_name:
                for signal in msg.getElementsByTagName("signal"):
                    for signalEnable in signal.getElementsByTagName('sigEnable'):
                        if signalEnable.firstChild.nodeValue == "TRUE":
                            for actualSig in signal.getElementsByTagName('actualSig'):
                                if actualSig.firstChild.nodeValue != "NUL":
                                    s += ('{0} = b_{1}_b;!'.format(
                                        actualSig.firstChild.nodeValue,
                                        actualSig.firstChild.nodeValue))
                                else:
                                    raise AttributeError(
                                        'signal {0} enabled but not mapped to a real signal'.format(
                                            signal.getElementsByTagName('predefinedSig')[0].firstChild.nodeValue))
        return s


if __name__ == "__main__":
    coco_configurator = CocoConfigurator(sys.argv[1])
    coco_configurator.generate_hfile(sys.argv[2])
    coco_configurator.generate_cfile(sys.argv[3])
