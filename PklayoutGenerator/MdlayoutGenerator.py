'''
Created on 22th, March, 2018

@author: Alvin Ye
'''

import sys

# add below to avoid the error of 'no module found' if running the script from .bat file
# in that case, modules are not in sys path, and can not be found automatically
sys.path.append('../')
sys.path.append('../../')
from PkdbcIterator.MddbcParser import DbcParser
from PkCanMsgLayoutComposer.MdCanMsgLayoutComposer import CanMsgLayoutComposer
from PklayoutGenerator.MdlayoutAnalyzer import SignalBitFieldGenerator

if __name__ == '__main__':
    s = ''
    # create a instance of DbcParser
    myParser = DbcParser()
    try:
        # sys.argv[1],[2],[3] are paths for dbc, input file, output file in order
        # will below, all dbc info is captured in attributes of myParser
        myParser.parser_dbc(sys.argv[1])
        print('[INFO]: dbc parsing succeed')
        with open(sys.argv[2], 'w') as hFile:
            hFile.write('#include "mq_type.h"\n')
            with open(sys.argv[3], 'w') as cFile:
                cFile.write('#include "I2CCAN_Par.h"\n')
                # iterate all msgs stored in node.node_tx_msgs and node.node_rx_msgs
                # for msg in list(myParser.can_network.nodes['ESCL'].node_tx_msgs.values()) + list(
                #         myParser.can_network.nodes['ESCL'].node_rx_msgs.values()):
                for msg in list(myParser.can_network.nodes[sys.argv[4]].node_rx_msgs.values()):
                    try:
                        # by default, it is treated as msg with multiplexer
                        # otherwise, an exception will be captured and code falls into the exception handler
                        # vritual_msg is different image of original msg by multiplexer_id
                        for virtual_msg in CanMsgLayoutComposer(
                                msg).compose_msg_with_multiplexer().node_tx_msgs.values():
                            hFile.write('\ntypedef struct _c_{0}_msg_typeTag\n'.format(virtual_msg.msg_name))
                            hFile.write('{\n')
                            composed_msg, sub_signals_group = CanMsgLayoutComposer(
                                virtual_msg).compose_msg_without_multiplexer()
                            # with returned composed msg for bif field analysis
                            generator = SignalBitFieldGenerator(composed_msg)
                            generator.bit_field_generator(hFile)
                            hFile.write('}')
                            s += '\t_c_{0}_msg_type {1};\n'.format(virtual_msg.msg_name, virtual_msg.msg_name)
                            hFile.write('_c_{0}_msg_type;\n'.format(virtual_msg.msg_name))
                            # for a msg with multiplexer, a union instead of structure will be created
                            generator.signal_union_generator(msg, hFile)
                            # with returned sub_signals_group for signal access macro generation
                            generator.signal_access_macro_syntax(sub_signals_group, hFile)
                        hFile.write('\ntypedef union _u_{0}_msg_typeTag\n'.format(msg.msg_name))
                        hFile.write('{\n')
                        hFile.write(s)
                        hFile.write('}')
                        hFile.write('_u_{0}_msg_type;\n'.format(msg.msg_name))
                        cFile.write('_u_{0}_msg_type\t\t{1};\n'.format(msg.msg_name, msg.msg_name))
                        hFile.write('extern _u_{0}_msg_type\t\t{1};\n'.format(msg.msg_name, msg.msg_name))
                    except TypeError or AttributeError:
                        hFile.write('\ntypedef struct _c_{0}_msg_typeTag\n'.format(msg.msg_name))
                        hFile.write('{\n')
                        composed_msg, sub_signals_group = CanMsgLayoutComposer(
                            msg).compose_msg_without_multiplexer()
                        # with returned composed msg for bif field analysis
                        generator = SignalBitFieldGenerator(composed_msg)
                        generator.bit_field_generator(hFile)
                        hFile.write('}')
                        hFile.write('_c_{0}_msg_type;\n'.format(msg.msg_name))
                        cFile.write('_c_{0}_msg_type\t\t{1};\n'.format(msg.msg_name, msg.msg_name))
                        hFile.write('extern _c_{0}_msg_type\t\t{1};\n'.format(msg.msg_name, msg.msg_name))
                        generator.signal_struct_generator(hFile)
                        # with returned sub_signals_group for signal access macro generation
                        generator.signal_access_macro_syntax(sub_signals_group, hFile)
        print('[INFO]: file generation succeed')
    except UnicodeDecodeError:
        print('[ERROR] dbc decoding error, please convert dbc to utf-8 first')
    except KeyError:
        print('[ERROR] please set the actual name of ESCL from dbc in .bat file')
    except FileNotFoundError:
        print('[ERROR]: no dbc file designated')
    except IndexError:
        print('[ERROR]: input or output directory is not properly given')
