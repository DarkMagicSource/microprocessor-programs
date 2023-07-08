import cv2
import numpy as np

def main():
    with open('video.h', 'w') as f:
        f.write('const uint8_t VIDEO[] PROGMEM = {\n')
        
        video = cv2.VideoCapture('bad_apple_24fps.mp4')
        
        count = 0
        success, image = video.read()
        while success:
            image = image[:, :, 0]
            image = cv2.resize(image, (16, 8), interpolation=cv2.INTER_CUBIC)

            row = []
            for c in range(16):
                data = sum(2**r if image[r, c] > 50 else 0 for r in range(8))
                row.append(hex(data) + ',')
            row = '    ' + ' '.join(row)
            f.write(row + '\n')
            
            success, image = video.read()
            count += 1
        
        f.write('};\n')
        f.write('const int N_FRAMES = ' + str(count) + ';\n')

if __name__ == '__main__':
    main()
