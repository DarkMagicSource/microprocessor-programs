import mido

START_DELAY = 1000

TONE_PREFIXES = [
    'NOTE_C',
    'NOTE_CS',
    'NOTE_D',
    'NOTE_DS',
    'NOTE_E',
    'NOTE_F',
    'NOTE_FS',
    'NOTE_G',
    'NOTE_GS',
    'NOTE_A',
    'NOTE_AS',
    'NOTE_B'
]

def note_to_tone(note):
    octave = note // 12
    prefix = TONE_PREFIXES[note % 12]
    return prefix + str(octave)

def main():
    delays = []
    tones = []

    with mido.MidiFile('bad_apple.mid', clip=True) as mid:
        for msg in mid:
            if msg.type == 'note_on':
                tones.append(note_to_tone(msg.note))
                delays.append(int(round(msg.time*1000)))
            elif msg.type == 'note_off':
                tones.append('NOTE_OFF')
                delays.append(int(round(msg.time*1000)))

    delays[0] += START_DELAY

    with open('audio.h', 'w') as f:
        f.write('#define NOTE_OFF 0\n')
        
        f.write('const uint16_t TONES[] PROGMEM = {\n')
        for tone in tones:
            f.write(f'    {tone},\n')
        f.write('};\n')

        f.write('const uint16_t DELAYS[] PROGMEM = {\n')
        for delay in delays:
            f.write(f'    {delay},\n')
        f.write('};\n')

        f.write(f'const int N_TONES = {len(tones)};')

if __name__ == '__main__':
    main()
