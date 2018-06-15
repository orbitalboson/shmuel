import ctypes
import mmap

def Crc8(buf, init=0xFF):
    crc = init
    
    for b in buf:
        crc ^= b
        for i in range(8):
            crc = (crc << 1) ^ 0x31 if (crc & 0x80) else crc << 1
            crc &= 0xff
    
    return crc

class RBFrameHeaderMain(ctypes.Structure):
    _fields_ = [("id", ctypes.c_int),
                ("payload_size", ctypes.c_size_t)]

class RBFrameHeader(ctypes.Structure):
    _fields_ = [("main", RBFrameHeaderMain),
                ("crc8", ctypes.c_uint8)]    
    

class Shmuel:
    def __init__(self, name, size, block_size):
        self.name = name
        self.size = size
        self.block_size = block_size
        self.file = None
        self.memory = None
       
       
        self.file = open('/dev/shm/'+self.name, 'br')
        self.memory = mmap.mmap(self.file.fileno(), size,  access=mmap.ACCESS_READ)
        
    def getBlock(self, num):
        buf = self.memory.seek(self.block_size * num)
        
        buf = self.memory.read(self.block_size)
        
        frame = RBFrameHeader()
        ctypes.memmove(ctypes.addressof(frame), buf, ctypes.sizeof(frame))
        
        block_crc = frame.crc8

        crc = Crc8(buf[0:ctypes.sizeof(RBFrameHeaderMain)])
        crc = Crc8(buf[ctypes.sizeof(RBFrameHeader):self.block_size], crc)

        
        if block_crc != crc:
            return None
        else:
            return ShmuelBlock(buf)
        
    def close(self):
        self.file.close()


class ShmuelBlock:
    def __init__(self, buf):
        frame = RBFrameHeader()
        ctypes.memmove(ctypes.addressof(frame), buf, ctypes.sizeof(frame))
        
        self.id = frame.main.id
        self.size = frame.main.payload_size
        self.crc8 = frame.crc8
        
        self.bytes = buf
        
    def getID(self):
        return self.id
    
    def getSize(self):
        return len(self.bytes)

    def getPayloadSize(self):
        return self.size