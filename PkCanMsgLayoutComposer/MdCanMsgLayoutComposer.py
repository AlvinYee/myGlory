'''
Created on 12th Mar, 2018

@author: Alvin Ye
'''
from PkdbcCoreModel.MdCoreModel import CanSignal
from PkdbcCoreModel.MdCoreModel import CanMsg
from PkdbcCoreModel.MdCoreModel import CanNode
import copy


class CanMsgLayoutComposer(object):
    '''
    supporting all kinds of gaps, different endian-ness, multiple-byte, multiplexer
    '''

    def __init__(self, msg):
        '''
        Constructor
        '''
        self._msg = msg
        self._sorted_signals = {}
        self.composed_msg = CanMsg(msg.msg_id, msg.msg_name, msg.msg_len, msg.msg_type, msg.msg_sender,
                                   msg.msg_receivers, msg.msg_send_type)

    def _sort_signal(self):
        '''
        to sort the signals in the msg by start bit and store them in self._sorted_signals
        '''
        for signal in self._msg.msg_signals.values():
            self._sorted_signals[signal.signal_start_bit] = signal
            #  sort signals in the dict by start bit, but return a list of tuples!
        self._sorted_signals = sorted(self._sorted_signals.items(), key=lambda d: d[0])

    def compose_msg_with_multiplexer(self):
        '''this func aims to compose multi-msg for multiplexer
        each msg is called virtual_msg
        a contained called virtual_node is created to hold these virtual msgs
        :return a virtual node that carries virtual msgs by different multiplexer id
        '''

        virtual_node = None
        virtual_msg = None
        multiplexer = None
        multiplexer_ids = []

        # iterate the message to find out he multiplexer first, this is a must
        # bug fix in case the first signal is not multiplexer
        for signal in self._msg.msg_signals.values():
            if signal.signal_multiplexer:
                # create virtual_node as a container for multi-msgs by different multiplexer_id
                virtual_node = CanNode('_virtual_node')
                # call this signal as multiplexer
                multiplexer = signal
                # create first virtual_msg with name followed by multiplexer,which is 'M'
                # the others will be followed by multiplexer_id, which is 'm1,m2...'
                virtual_msg = CanMsg(self._msg.msg_id, self._msg.msg_name + "M", self._msg.msg_len)
        # iterate each signal in the msg that has a multiplexer
        for signal in self._msg.msg_signals.values():
            # if it has a multiplexer
            if signal.signal_multiplexer:
                # add signal to this virtual_msg, usually it only contains one signal - the multiplexer
                virtual_msg.append_signal(signal.signal_name, signal)
                # to hold the virtual msg in the container - virtual node
                virtual_node.append_tx_msg(virtual_msg.msg_name, virtual_msg)
            # to avoid the case that multi-msgs are created for single multiplexer_id
            elif signal.signal_multiplexer_id not in multiplexer_ids and not signal.signal_multiplexer:
                # add the multiplexer id to known ids
                multiplexer_ids.append(signal.signal_multiplexer_id)
                # create virtual msg for this multiplexer id
                virtual_msg = CanMsg(self._msg.msg_id, self._msg.msg_name + signal.signal_multiplexer_id,
                                     self._msg.msg_len)
                # below is very important, to avoid corrupt original data integrity, a copy is needed
                # e.g., to append the signal to a virtual msg will broke the original msg carrier
                # the virtual msg carrying multiplexer
                multiplexer = copy.deepcopy(multiplexer)
                # due to above operation, now it is safe to append this signal to a new msg
                # otherwise, msg carrier will be corrupted
                virtual_msg.append_signal(multiplexer.signal_name, multiplexer)
                # this new virtual msg also contains the multiplexer, and all other signals
                virtual_msg.append_signal(signal.signal_name, signal)
                # now put the virtual msg to virtual node
                virtual_node.append_tx_msg(virtual_msg.msg_name, virtual_msg)
            # in the case the signal belongs a known virtual msg that hold the same multiplexer id
            elif signal.signal_multiplexer_id in multiplexer_ids and not signal.signal_multiplexer:
                # in this case , not needed to create a new virtual msg
                # just put the signal in the virtual msg that holds the same multiplexer id
                virtual_node.node_tx_msgs[self._msg.msg_name + signal.signal_multiplexer_id].append_signal(
                    signal.signal_name, signal)
            else:
                raise AttributeError
        return virtual_node

    def compose_msg_without_multiplexer(self):
        '''this func aims to compose a new msg based on original msg with gap signal and sub signals that from a
        msg that is over byte boundary or multi-byte signal
        :return this new msg as described
        '''
        # below is very important variable
        # it always points to the first bit that is not used in that byte
        unused_bits_head = [0 for i in range(0, self._msg.msg_len)]
        gap_syntax = 'unused'
        gap_idx = 0
        multi_byte_idx = 0
        tail_bit = 7
        sub_signal = None
        gap = None
        # sub signals always has the original signal at the beginning of the list
        # so that code generation for across-byte signal access macro will be easier
        sub_signals = []
        # this group just wrap sub signals into a list for easy iteration, so it is a list of list
        sub_signals_group = []

        # sort signals in the msg by start bit
        self._sort_signal()
        # iterate each byte in the msg
        for byteIdx in range(0, self._msg.msg_len):
            # create a copy in order not to change the indexer
            byte_idx_temp = byteIdx
            # now iterate each signal in the msg 
            for (start_bit, signal) in self._sorted_signals:
                #  now check if the signal's start bit falls in the byte from outer loop
                if byteIdx * 8 <= start_bit <= (byteIdx + 1) * 8 - 1:
                    #  is it Intel?
                    if signal.signal_little_endian > 0:
                        #  is it multi-byte or across byte boundary?
                        # CAUTION: here use byte_idx_temp, in while hoop for multi-byte,it is byteIdx used
                        if unused_bits_head[byteIdx] + signal.signal_len < 9:
                            #  check any gap to the left of the signal ?
                            if start_bit % 8 != unused_bits_head[byteIdx]:
                                #  create gap signal
                                # gap = CanSignal(gap_syntax + str(gap_idx),
                                #                 unused_bits_head[byteIdx],
                                #                 start_bit % 8 - unused_bits_head[byteIdx],
                                #                 little_endian=1,
                                #                 msg_carrier=signal.signal_msg_carrier)
                                # CR1-keep accurate start bit
                                gap = CanSignal(gap_syntax + str(gap_idx),
                                                unused_bits_head[byteIdx] + 8 * byteIdx,
                                                start_bit % 8 - unused_bits_head[byteIdx],
                                                little_endian=1,
                                                msg_carrier=signal.signal_msg_carrier)
                                # put the gap signal into composed msg
                                self.composed_msg.append_signal(gap_syntax + str(gap_idx),
                                                                gap)
                                #  shift unused bit position
                                unused_bits_head[byteIdx] = start_bit % 8
                                gap_idx += 1
                            # if not gap, append the signal to the composed msg
                            # similarly, in order not to corrupt the signal, create a copy
                            # start bit is transferred to bit shift
                            # signal = CanSignal(signal.signal_name, signal.signal_start_bit % 8,
                            #                    signal.signal_len, little_endian=1,
                            #                    msg_carrier=signal.signal_msg_carrier)
                            # new implementation, keep start bit
                            signal = CanSignal(signal.signal_name, signal.signal_start_bit,
                                               signal.signal_len, little_endian=1,
                                               msg_carrier=signal.signal_msg_carrier)
                            self.composed_msg.append_signal(signal.signal_name, signal)
                            #  tracking unused bit
                            unused_bits_head[byteIdx] += signal.signal_len
                        else:
                            # put the original at the beginning of the list
                            sub_signals.append(copy.deepcopy(signal))
                            while signal.signal_len + unused_bits_head[byte_idx_temp] > 8:
                                # also need to check if any gap to the left for Intel multi-byte case
                                # for motorola, not necessary, because of growth direction
                                if start_bit % 8 != unused_bits_head[byte_idx_temp]:
                                    gap = CanSignal(gap_syntax + str(gap_idx),
                                                    unused_bits_head[byte_idx_temp] + 8 * byte_idx_temp,
                                                    start_bit % 8 - unused_bits_head[byte_idx_temp],
                                                    little_endian=1,
                                                    msg_carrier=signal.signal_msg_carrier)
                                    # put the gap signal into composed msg
                                    self.composed_msg.append_signal(gap_syntax + str(gap_idx),
                                                                    gap)
                                    #  shift unused bit position
                                    unused_bits_head[byte_idx_temp] = start_bit % 8
                                    gap_idx += 1
                                # create sub signal
                                # sub_signal = CanSignal(signal.signal_name + str(multi_byte_idx),
                                #                        signal.signal_start_bit % 8,
                                #                        tail_bit - unused_bits_head[byteIdx] + 1,
                                #                        little_endian=1,
                                #                        msg_carrier=signal.signal_msg_carrier)
                                # CR1-keep accurate start bit
                                sub_signal = CanSignal(signal.signal_name + str(multi_byte_idx),
                                                       signal.signal_start_bit,
                                                       tail_bit - unused_bits_head[byte_idx_temp] + 1,
                                                       little_endian=1,
                                                       msg_carrier=signal.signal_msg_carrier)
                                # put sub signal in composed msg
                                self.composed_msg.append_signal(signal.signal_name + str(multi_byte_idx),
                                                                sub_signal)
                                # put the sub signal into the list - sub signals
                                sub_signals.append(sub_signal)
                                multi_byte_idx += 1
                                # remove the sub signal
                                signal.signal_len -= tail_bit - unused_bits_head[byte_idx_temp] + 1
                                # shift  signal start bit
                                # signal.signal_start_bit += tail_bit - unused_bits_head[byteIdx] + 1
                                # CR1-keep accurate start bit
                                signal.signal_start_bit += tail_bit - unused_bits_head[byte_idx_temp] + 1
                                #  set current byte to be full
                                unused_bits_head[byte_idx_temp] = tail_bit + 1
                                if byte_idx_temp < 7:
                                    byte_idx_temp += 1
                            else:
                                #  create signal within signal byte
                                # sub_signal = CanSignal(signal.signal_name + str(multi_byte_idx),
                                #                        signal.signal_start_bit % 8, signal.signal_len,
                                #                        little_endian=1,
                                #                        msg_carrier=signal.signal_msg_carrier)
                                # CR1-keep accurate start bit
                                sub_signal = CanSignal(signal.signal_name + str(multi_byte_idx),
                                                       signal.signal_start_bit, signal.signal_len,
                                                       little_endian=1,
                                                       msg_carrier=signal.signal_msg_carrier)
                                # put sub signal in composed msg
                                self.composed_msg.append_signal(signal.signal_name + str(multi_byte_idx),
                                                                sub_signal)
                                # put the sub signal into the list - sub signals
                                sub_signals.append(sub_signal)
                                multi_byte_idx = 0
                                #  unusedBits needs to shifted 
                                unused_bits_head[byte_idx_temp] += signal.signal_len
                    else:
                        #  this is Motorola
                        #  check multiple-byte?
                        if unused_bits_head[byteIdx] + signal.signal_len < 9:
                            #  check any gap to the left of the signal
                            if start_bit % 8 + 1 - signal.signal_len > unused_bits_head[byteIdx]:
                                # create gap signal
                                # gap = CanSignal(gap_syntax + str(gap_idx),
                                #                 unused_bits_head[byteIdx],
                                #                 start_bit % 8 - signal.signal_len + 1 -
                                #                 unused_bits_head[byteIdx], little_endian=1,
                                #                 msg_carrier=signal.signal_msg_carrier)
                                # CR1-keep accurate start bit
                                gap = CanSignal(gap_syntax + str(gap_idx),
                                                unused_bits_head[byteIdx] + 8 * byteIdx,
                                                start_bit % 8 - signal.signal_len + 1 -
                                                unused_bits_head[byteIdx], little_endian=1,
                                                msg_carrier=signal.signal_msg_carrier)
                                # put the gap signal into composed msg
                                self.composed_msg.append_signal(gap_syntax + str(gap_idx), gap)
                                # shift unused bit position
                                unused_bits_head[byteIdx] = start_bit % 8 - signal.signal_len + 1
                                gap_idx += 1
                            # similarly, in order not to corrupt the signal, create a copy
                            # start bit is transferred to bit shift
                            # signal = CanSignal(signal.signal_name + str(multi_byte_idx),
                            #                    signal.signal_start_bit % 8, signal.signal_len,
                            #                    little_endian=0,
                            #                    msg_carrier=signal.signal_msg_carrier)
                            # CR1-keep accurate start bit
                            signal = CanSignal(signal.signal_name,
                                               signal.signal_start_bit, signal.signal_len,
                                               little_endian=0,
                                               msg_carrier=signal.signal_msg_carrier)
                            self.composed_msg.append_signal(signal.signal_name, signal)
                            unused_bits_head[byteIdx] += signal.signal_len
                        else:
                            # put the original signal at the beginning of the list
                            sub_signals.append(copy.deepcopy(signal))
                            while signal.signal_start_bit % 8 + 1 - unused_bits_head[byte_idx_temp] < signal.signal_len:
                                # sub_signal = CanSignal(signal.signal_name + str(multi_byte_idx),
                                #                        signal.signal_start_bit % 8,
                                #                        signal.signal_start_bit % 8 + 1,
                                #                        little_endian=0,
                                #                        msg_carrier=signal.signal_msg_carrier)
                                # CR1-keep accurate start bit
                                sub_signal = CanSignal(signal.signal_name + str(multi_byte_idx),
                                                       signal.signal_start_bit,
                                                       signal.signal_start_bit % 8 + 1,
                                                       little_endian=0,
                                                       msg_carrier=signal.signal_msg_carrier)
                                self.composed_msg.append_signal(signal.signal_name + str(multi_byte_idx),
                                                                sub_signal)
                                sub_signals.append(sub_signal)
                                multi_byte_idx += 1
                                signal.signal_len -= signal.signal_start_bit % 8 - unused_bits_head[byte_idx_temp] + 1
                                unused_bits_head[byte_idx_temp] = signal.signal_start_bit % 8 + 1
                                signal.signal_start_bit = 8 * (byte_idx_temp + 2) - 1
                                if byte_idx_temp < 7:
                                    byte_idx_temp += 1
                            else:
                                # create signal within signal byte
                                # sub_signal = CanSignal(signal.signal_name + str(multi_byte_idx),
                                #                        signal.signal_start_bit % 8, signal.signal_len,
                                #                        little_endian=0,
                                #                        msg_carrier=signal.signal_msg_carrier)
                                # CR1-keep accurate start bit
                                sub_signal = CanSignal(signal.signal_name + str(multi_byte_idx),
                                                       signal.signal_start_bit, signal.signal_len,
                                                       little_endian=0,
                                                       msg_carrier=signal.signal_msg_carrier)
                                self.composed_msg.append_signal(signal.signal_name + str(multi_byte_idx),
                                                                sub_signal)
                                sub_signals.append(sub_signal)
                                multi_byte_idx = 0
                                unused_bits_head[byte_idx_temp] = signal.signal_start_bit % 8 + 1
                if len(sub_signals):
                    sub_signals_group.append(copy.deepcopy(sub_signals))
                # whatever there is sub signal, sub signals reference must be cleared for next loop
                sub_signals.clear()
            # gap stuffing from right direction
            if unused_bits_head[byteIdx] <= tail_bit:
                # CR1-keep accurate start bit
                gap = CanSignal(gap_syntax + str(gap_idx),
                                unused_bits_head[byteIdx] + 8 * byteIdx,
                                tail_bit - unused_bits_head[byteIdx] + 1,
                                little_endian=1,
                                msg_carrier=signal.signal_msg_carrier)
                self.composed_msg.append_signal(gap_syntax + str(gap_idx), gap)
                gap_idx += 1
                unused_bits_head[byteIdx] = tail_bit + 1
        return self.composed_msg, sub_signals_group
