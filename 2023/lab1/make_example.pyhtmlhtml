import struct

def write_list_to_file(data_list, ofname):
  format_only = [ x[0] for x in data_list]
  data_only = [x[1] for x in data_list]
  print('=' + ''.join(format_only))
  print(data_only)
  of = open(ofname, 'wb')
  of.write(struct.pack('='+'c'*(len(format_only)), *[bytes(c, "utf-8") for c in format_only]))
  of.write(struct.pack('=c', b'e'))
  of.write(struct.pack('='+''.join(format_only), *data_only))
  padding = 100 - of.tell()
  of.write(struct.pack('={}b'.format(padding), *bytearray(padding)))
  of.close()

# 'b' = signed char, 'i' = 4 byte int, 'd' = 8 byte double
# 'B' = unsigned char, 'I' = unsigned int, 'h' = 2 byte int

example1 = [('b',-100), ('i',-100), ('d', -100.0), ('i', -100), ('d', -100.0), ('b', -100)]
example2 = [('i',10000), ('b',-100), ('b', -100), ('b', -100), ('b', -100), ('b', -100)]
example3 = [('d',1e7), ('i',10000), ('b',-100), ('b', -100), ('b', -100), ('b', -100), ('b', -100)]

write_list_to_file(example1, 'example1.bin')
write_list_to_file(example2, 'example2.bin')
write_list_to_file(example3, 'example3.bin')


