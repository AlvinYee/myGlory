import sys

sys.path.append('../')
sys.path.append('../../')
import re


class CocoCfgValidator(object):
    def __init__(self, xml_doc):
        self._check_patten(xml_doc)
        self._check_tags(xml_doc)
        self._check_constraints(xml_doc)
        self._check_consistency(xml_doc)

    @staticmethod
    def _check_patten(xml_doc):
        for tag in ('Parameter', 'I2CMsg', 'signal'):
            for node in xml_doc.getElementsByTagName(tag):
                for element in node.childNodes:
                    if element.nodeName not in ('#text', 'signals'):
                        pattern = element.getAttribute("constraints")
                        line = element.firstChild.nodeValue
                        reg = re.fullmatch(pattern, line)
                        if not reg:
                            raise AttributeError('[ERROR]: {0} is not a valid configuration'.format(line))

    @staticmethod
    def _check_tags(xml_doc):
        parameter_tags = ('predefinedPar', 'actualValue', '#text')
        i2cmsg_tags = (
            'predefinedPar', 'actualValue', 'I2CMsg', 'predefinedMsg', 'actualMsg', 'msgEnable', 'timeoutMonitor',
            'timeoutValue', 'CRCcheck', 'crcOffset', 'aliveCntCheck', 'aliveCntMax', 'aliveCntIncMin', 'aliveCntIncMax',
            'qualCheck', 'qualTime', 'funcCode', 'msgLength', 'msgLcdSda', 'msgLcdSdaInv', 'msgLcdSdaID',
            'msgLcdSdaTrue', 'msgLcdSdaFalse', 'msgQualCntSda', 'msgQualCntSdaInv', 'msgQualCntSdaID', 'signals',
            '#text')
        signal_tag = (
            'predefinedSig', 'actualSig', 'sigEnable', 'initValue', 'defaultValue', 'sigSdaStorage', 'sigSdaStorageInv',
            'sigSdaID', '#text')
        tag_dic = {'Parameter': parameter_tags,
                   'I2CMsg': i2cmsg_tags,
                   'signal': signal_tag}
        for element_tag, sub_element_tag in tag_dic.items():
            elements = xml_doc.getElementsByTagName(element_tag)
            if not elements:
                raise AttributeError('[INFO]: no {0} defined as expected'.format(element_tag))
            for element in elements:
                for sub_element in element.childNodes:
                    if sub_element.nodeName not in sub_element_tag:
                        raise AttributeError('[INFO]: {0} is not a valid tag'.format(sub_element.nodeName))

    @staticmethod
    def _check_constraints(xml_doc):
        even_numbers = ('qualTime', 'timeoutValue')
        limited_numbers = ('timeoutValue', 'qualTime', 'initValue', 'defaultValue')
        for tag in even_numbers:
            for element in xml_doc.getElementsByTagName(tag):
                if element.firstChild.nodeValue not in ('NULL', 'NUL'):
                    if int(element.firstChild.nodeValue) % 2 != 0:
                        raise AttributeError('{0} must be multiple of 2'.format(tag))
        for tag in limited_numbers:
            for element in xml_doc.getElementsByTagName(tag):
                if element.firstChild.nodeValue not in ('NULL', 'NUL'):
                    if not 0 <= int(element.firstChild.nodeValue) <= 65535:
                        raise AttributeError('{0} must be between 0 and 65535'.format(tag))

    @staticmethod
    def _check_consistency(xml_doc):
        msg_constraints = {
            'msgEnable': ('actualMsg', 'msgLcdSda', 'msgLcdSdaInv', 'msgLcdSdaID', 'msgLcdSdaTrue', 'msgLcdSdaFalse', 'funcCode', 'msgLength'),
            'timeoutMonitor': ('timeoutValue',),
            'aliveCntCheck': ('aliveCntMax', 'aliveCntIncMin', 'aliveCntIncMax'),
            'qualCheck': ('qualTime', 'msgQualCntSda', 'msgQualCntSdaInv', 'msgQualCntSdaID')
        }
        signal_constraints = {
            'sigEnable': ('actualSig', 'initValue')
        }
        for msg in xml_doc.getElementsByTagName('I2CMsg'):
            for l, f in msg_constraints.items():
                if msg.getElementsByTagName(l)[0].firstChild.nodeValue == 'TRUE':
                    for tag in f:
                        if msg.getElementsByTagName(tag)[0].firstChild.nodeValue in ('NULL', 'NUL'):
                            raise AttributeError('{0} must not be NULl or NUL when {1} is enabled '.format(tag,
                                                 msg.getElementsByTagName(l)[0].nodeName))
                else:
                    for tag in f:
                        if msg.getElementsByTagName(tag)[0].firstChild.nodeValue not in ('NULL', 'NUL'):
                            raise AttributeError('{0} must  be NULl or NUL when {1} is disabled '.format(tag,
                                                 msg.getElementsByTagName(l)[0].nodeName))

        for signal in xml_doc.getElementsByTagName('signal'):
            for l, f in signal_constraints.items():
                if signal.getElementsByTagName(l)[0].firstChild.nodeValue == 'TRUE':
                    for tag in f:
                        if signal.getElementsByTagName(tag)[0].firstChild.nodeValue in ('NULL', 'NUL'):
                            raise AttributeError('{0} must not be NULl or NUL when {1} is enabled '.format(tag,
                                                 signal.getElementsByTagName(l)[0].nodeName))
                else:
                    for tag in f:
                        if signal.getElementsByTagName(tag)[0].firstChild.nodeValue not in ('NULL', 'NUL'):
                            raise AttributeError('{0} must be NULl or NUL when {1} is disabled '.format(tag,
                                                 signal.getElementsByTagName(l)[0].nodeName))
