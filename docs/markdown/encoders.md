# Audio encoders

----------------------------------------

## AAC audio encoder

### RAW (.mp4)

#### 0x28 Unknwon Profile

| kbps     | bits     | chan     | rate     |  profile (payload)                    |
|---------:|---------:|:--------:|---------:|:--------------------------------------|
|        8 |       16 |        1 |    11025 |  0x28  Unknown Profile       (0 RAW)  |
|        8 |       16 |        1 |    16000 |  0x28  Unknown Profile       (0 RAW)  |
|       12 |       16 |        1 |    11025 |  0x28  Unknown Profile       (0 RAW)  |
|       12 |       16 |        1 |    16000 |  0x28  Unknown Profile       (0 RAW)  |
|       16 |       16 |        1 |    11025 |  0x28  Unknown Profile       (0 RAW)  |
|       16 |       16 |        1 |    16000 |  0x28  Unknown Profile       (0 RAW)  |
|       16 |       16 |        2 |    11025 |  0x28  Unknown Profile       (0 RAW)  |
|       16 |       16 |        2 |    16000 |  0x28  Unknown Profile       (0 RAW)  |
|       24 |       16 |        1 |    16000 |  0x28  Unknown Profile       (0 RAW)  |
|       24 |       16 |        1 |    22050 |  0x28  Unknown Profile       (0 RAW)  |
|       24 |       16 |        1 |    24000 |  0x28  Unknown Profile       (0 RAW)  |
|       24 |       16 |        2 |    16000 |  0x28  Unknown Profile       (0 RAW)  |
|       32 |       16 |        1 |    16000 |  0x28  Unknown Profile       (0 RAW)  |
|       32 |       16 |        1 |    22050 |  0x28  Unknown Profile       (0 RAW)  |
|       32 |       16 |        2 |    16000 |  0x28  Unknown Profile       (0 RAW)  |
|       32 |       16 |        2 |    22050 |  0x28  Unknown Profile       (0 RAW)  |
|       32 |       16 |        2 |    24000 |  0x28  Unknown Profile       (0 RAW)  |

#### 0x29 AAC Profile L2

| kbps     | bits     | chan     | rate     |  profile (payload)                    |
|---------:|---------:|:--------:|---------:|:--------------------------------------|
|       32 |       16 |        1 |    24000 |  0x29  AAC Profile L2        (0 RAW)  |
|       48 |       16 |        1 |    32000 |  0x29  AAC Profile L2        (0 RAW)  |
|       48 |       16 |        1 |    44100 |  0x29  AAC Profile L2        (0 RAW)  |
|       48 |       16 |        1 |    48000 |  0x29  AAC Profile L2        (0 RAW)  |
|       48 |       16 |        2 |    32000 |  0x29  AAC Profile L2        (0 RAW)  |
|       64 |       16 |        1 |    32000 |  0x29  AAC Profile L2        (0 RAW)  |
|       64 |       16 |        1 |    44100 |  0x29  AAC Profile L2        (0 RAW)  |
|       64 |       16 |        1 |    48000 |  0x29  AAC Profile L2        (0 RAW)  |
|       64 |       16 |        2 |    32000 |  0x29  AAC Profile L2        (0 RAW)  |
|       96 |       16 |        1 |    32000 |  0x29  AAC Profile L2        (0 RAW)  |
|       96 |       16 |        1 |    44100 |  0x29  AAC Profile L2        (0 RAW)  |
|       96 |       16 |        1 |    48000 |  0x29  AAC Profile L2        (0 RAW)  |
|       96 |       16 |        2 |    32000 |  0x29  AAC Profile L2        (0 RAW)  |
|       96 |       16 |        2 |    44100 |  0x29  AAC Profile L2        (0 RAW)  |
|       96 |       16 |        2 |    48000 |  0x29  AAC Profile L2        (0 RAW)  |
|      128 |       16 |        1 |    32000 |  0x29  AAC Profile L2        (0 RAW)  |
|      128 |       16 |        1 |    44100 |  0x29  AAC Profile L2        (0 RAW)  |
|      128 |       16 |        1 |    48000 |  0x29  AAC Profile L2        (0 RAW)  |
|      128 |       16 |        2 |    32000 |  0x29  AAC Profile L2        (0 RAW)  |
|      128 |       16 |        2 |    44100 |  0x29  AAC Profile L2        (0 RAW)  |
|      128 |       16 |        2 |    48000 |  0x29  AAC Profile L2        (0 RAW)  |
|      160 |       16 |        1 |    44100 |  0x29  AAC Profile L2        (0 RAW)  |
|      160 |       16 |        1 |    48000 |  0x29  AAC Profile L2        (0 RAW)  |
|      160 |       16 |        2 |    44100 |  0x29  AAC Profile L2        (0 RAW)  |
|      160 |       16 |        2 |    48000 |  0x29  AAC Profile L2        (0 RAW)  |
|      192 |       16 |        1 |    44100 |  0x29  AAC Profile L2        (0 RAW)  |
|      192 |       16 |        1 |    48000 |  0x29  AAC Profile L2        (0 RAW)  |
|      192 |       16 |        2 |    32000 |  0x29  AAC Profile L2        (0 RAW)  |
|      192 |       16 |        2 |    44100 |  0x29  AAC Profile L2        (0 RAW)  |
|      192 |       16 |        2 |    48000 |  0x29  AAC Profile L2        (0 RAW)  |
|      256 |       16 |        2 |    32000 |  0x29  AAC Profile L2        (0 RAW)  |
|      256 |       16 |        2 |    44100 |  0x29  AAC Profile L2        (0 RAW)  |
|      256 |       16 |        2 |    48000 |  0x29  AAC Profile L2        (0 RAW)  |
|      320 |       16 |        2 |    32000 |  0x29  AAC Profile L2        (0 RAW)  |
|      320 |       16 |        2 |    44100 |  0x29  AAC Profile L2        (0 RAW)  |
|      320 |       16 |        2 |    48000 |  0x29  AAC Profile L2        (0 RAW)  |

#### 0x2A AAC Profile L4

| kbps     | bits     | chan     | rate     |  profile (payload)                    |
|---------:|---------:|:--------:|---------:|:--------------------------------------|
|      128 |       16 |        6 |    32000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      128 |       16 |        6 |    44100 |  0x2A  AAC Profile L4        (0 RAW)  |
|      128 |       16 |        6 |    48000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      192 |       16 |        6 |    32000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      192 |       16 |        6 |    44100 |  0x2A  AAC Profile L4        (0 RAW)  |
|      192 |       16 |        6 |    48000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      256 |       16 |        6 |    32000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      256 |       16 |        6 |    44100 |  0x2A  AAC Profile L4        (0 RAW)  |
|      256 |       16 |        6 |    48000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      320 |       16 |        6 |    32000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      320 |       16 |        6 |    44100 |  0x2A  AAC Profile L4        (0 RAW)  |
|      320 |       16 |        6 |    48000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      480 |       16 |        6 |    32000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      480 |       16 |        6 |    44100 |  0x2A  AAC Profile L4        (0 RAW)  |
|      480 |       16 |        6 |    48000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      512 |       16 |        6 |    32000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      512 |       16 |        6 |    44100 |  0x2A  AAC Profile L4        (0 RAW)  |
|      512 |       16 |        6 |    48000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      576 |       16 |        6 |    44100 |  0x2A  AAC Profile L4        (0 RAW)  |
|      576 |       16 |        6 |    48000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      640 |       16 |        6 |    32000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      640 |       16 |        6 |    44100 |  0x2A  AAC Profile L4        (0 RAW)  |
|      640 |       16 |        6 |    48000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      720 |       16 |        6 |    32000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      720 |       16 |        6 |    44100 |  0x2A  AAC Profile L4        (0 RAW)  |
|      720 |       16 |        6 |    48000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      768 |       16 |        6 |    44100 |  0x2A  AAC Profile L4        (0 RAW)  |
|      768 |       16 |        6 |    48000 |  0x2A  AAC Profile L4        (0 RAW)  |
|      960 |       16 |        6 |    44100 |  0x2A  AAC Profile L4        (0 RAW)  |
|      960 |       16 |        6 |    48000 |  0x2A  AAC Profile L4        (0 RAW)  |
|     1152 |       16 |        6 |    44100 |  0x2A  AAC Profile L4        (0 RAW)  |
|     1152 |       16 |        6 |    48000 |  0x2A  AAC Profile L4        (0 RAW)  |

#### 0x2B AAC Profile L5

| kbps     | bits     | chan     | rate     |  profile (payload)                    |
|---------:|---------:|:--------:|---------:|:--------------------------------------|
|      320 |       16 |        2 |    96000 |  0x2B  AAC Profile L5        (0 RAW)  |

#### 0x2C HE-AAC v1 Profile L2

| kbps     | bits     | chan     | rate     |  profile (payload)                    |
|---------:|---------:|:--------:|---------:|:--------------------------------------|
|       12 |       16 |        1 |    24000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       16 |       16 |        1 |    32000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       16 |       16 |        2 |    32000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       16 |       16 |        2 |    44100 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       16 |       16 |        2 |    48000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       24 |       16 |        1 |    32000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       24 |       16 |        2 |    32000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       24 |       16 |        2 |    44100 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       24 |       16 |        2 |    48000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       32 |       16 |        1 |    32000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       32 |       16 |        2 |    32000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       32 |       16 |        2 |    44100 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       32 |       16 |        2 |    48000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       48 |       16 |        1 |    32000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       48 |       16 |        1 |    44100 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       48 |       16 |        1 |    48000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       48 |       16 |        2 |    32000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       48 |       16 |        2 |    44100 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       48 |       16 |        2 |    48000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       64 |       16 |        2 |    32000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       64 |       16 |        2 |    44100 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       64 |       16 |        2 |    48000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       96 |       16 |        2 |    32000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       96 |       16 |        2 |    44100 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |
|       96 |       16 |        2 |    48000 |  0x2C  HE-AAC v1 Profile L2  (0 RAW)  |

#### 0x2E HE-AAC v1 Profile L4

| kbps     | bits     | chan     | rate     |  profile (payload)                    |
|---------:|---------:|:--------:|---------:|:--------------------------------------|
|       64 |       16 |        6 |    32000 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |
|       64 |       16 |        6 |    44100 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |
|       64 |       16 |        6 |    48000 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |
|       96 |       16 |        6 |    32000 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |
|       96 |       16 |        6 |    44100 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |
|       96 |       16 |        6 |    48000 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |
|      128 |       16 |        6 |    32000 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |
|      128 |       16 |        6 |    44100 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |
|      128 |       16 |        6 |    48000 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |
|      192 |       16 |        6 |    32000 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |
|      192 |       16 |        6 |    44100 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |
|      192 |       16 |        6 |    48000 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |
|      256 |       16 |        6 |    32000 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |
|      256 |       16 |        6 |    44100 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |
|      256 |       16 |        6 |    48000 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |
|      320 |       16 |        6 |    32000 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |
|      320 |       16 |        6 |    44100 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |
|      320 |       16 |        6 |    48000 |  0x2E  HE-AAC v1 Profile L4  (0 RAW)  |

#### 0x30 HE-AAC v2 Profile L2

| kbps     | bits     | chan     | rate     |  profile (payload)                    |
|---------:|---------:|:--------:|---------:|:--------------------------------------|
|       12 |       16 |        2 |    22050 |  0x30  HE-AAC v2 Profile L2  (0 RAW)  |
|       12 |       16 |        2 |    24000 |  0x30  HE-AAC v2 Profile L2  (0 RAW)  |
|       12 |       16 |        2 |    32000 |  0x30  HE-AAC v2 Profile L2  (0 RAW)  |
|       16 |       16 |        2 |    32000 |  0x30  HE-AAC v2 Profile L2  (0 RAW)  |
|       24 |       16 |        2 |    44100 |  0x30  HE-AAC v2 Profile L2  (0 RAW)  |
|       24 |       16 |        2 |    48000 |  0x30  HE-AAC v2 Profile L2  (0 RAW)  |
|       32 |       16 |        2 |    44100 |  0x30  HE-AAC v2 Profile L2  (0 RAW)  |
|       32 |       16 |        2 |    48000 |  0x30  HE-AAC v2 Profile L2  (0 RAW)  |
|       48 |       16 |        2 |    44100 |  0x30  HE-AAC v2 Profile L2  (0 RAW)  |
|       48 |       16 |        2 |    48000 |  0x30  HE-AAC v2 Profile L2  (0 RAW)  |

#### 0x50 Unknown Profile

| kbps     | bits     | chan     | rate     |  profile (payload)                    |
|---------:|---------:|:--------:|---------:|:--------------------------------------|
|      256 |       16 |        8 |    32000 |  0x50  Unknown Profile       (0 RAW)  |
|      256 |       16 |        8 |    44100 |  0x50  Unknown Profile       (0 RAW)  |
|      256 |       16 |        8 |    48000 |  0x50  Unknown Profile       (0 RAW)  |
|      320 |       16 |        8 |    32000 |  0x50  Unknown Profile       (0 RAW)  |
|      320 |       16 |        8 |    44100 |  0x50  Unknown Profile       (0 RAW)  |
|      320 |       16 |        8 |    48000 |  0x50  Unknown Profile       (0 RAW)  |
|      480 |       16 |        8 |    32000 |  0x50  Unknown Profile       (0 RAW)  |
|      480 |       16 |        8 |    44100 |  0x50  Unknown Profile       (0 RAW)  |
|      480 |       16 |        8 |    48000 |  0x50  Unknown Profile       (0 RAW)  |
|      512 |       16 |        8 |    32000 |  0x50  Unknown Profile       (0 RAW)  |
|      512 |       16 |        8 |    44100 |  0x50  Unknown Profile       (0 RAW)  |
|      512 |       16 |        8 |    48000 |  0x50  Unknown Profile       (0 RAW)  |
|      640 |       16 |        8 |    32000 |  0x50  Unknown Profile       (0 RAW)  |
|      640 |       16 |        8 |    44100 |  0x50  Unknown Profile       (0 RAW)  |
|      640 |       16 |        8 |    48000 |  0x50  Unknown Profile       (0 RAW)  |
|      720 |       16 |        8 |    32000 |  0x50  Unknown Profile       (0 RAW)  |
|      720 |       16 |        8 |    44100 |  0x50  Unknown Profile       (0 RAW)  |
|      720 |       16 |        8 |    48000 |  0x50  Unknown Profile       (0 RAW)  |

#### 0x52 Unknown Profile

| kbps     | bits     | chan     | rate     |  profile (payload)                    |
|---------:|---------:|:--------:|---------:|:--------------------------------------|
|       64 |       16 |        8 |    32000 |  0x52  Unknown Profile       (0 RAW)  |
|       64 |       16 |        8 |    44100 |  0x52  Unknown Profile       (0 RAW)  |
|       64 |       16 |        8 |    48000 |  0x52  Unknown Profile       (0 RAW)  |
|       96 |       16 |        8 |    32000 |  0x52  Unknown Profile       (0 RAW)  |
|       96 |       16 |        8 |    44100 |  0x52  Unknown Profile       (0 RAW)  |
|       96 |       16 |        8 |    48000 |  0x52  Unknown Profile       (0 RAW)  |
|      128 |       16 |        8 |    32000 |  0x52  Unknown Profile       (0 RAW)  |
|      128 |       16 |        8 |    44100 |  0x52  Unknown Profile       (0 RAW)  |
|      128 |       16 |        8 |    48000 |  0x52  Unknown Profile       (0 RAW)  |
|      192 |       16 |        8 |    32000 |  0x52  Unknown Profile       (0 RAW)  |
|      192 |       16 |        8 |    44100 |  0x52  Unknown Profile       (0 RAW)  |
|      192 |       16 |        8 |    48000 |  0x52  Unknown Profile       (0 RAW)  |
|      256 |       16 |        8 |    32000 |  0x52  Unknown Profile       (0 RAW)  |
|      256 |       16 |        8 |    44100 |  0x52  Unknown Profile       (0 RAW)  |
|      256 |       16 |        8 |    48000 |  0x52  Unknown Profile       (0 RAW)  |
|      320 |       16 |        8 |    32000 |  0x52  Unknown Profile       (0 RAW)  |
|      320 |       16 |        8 |    44100 |  0x52  Unknown Profile       (0 RAW)  |
|      320 |       16 |        8 |    48000 |  0x52  Unknown Profile       (0 RAW)  |

### ADTS (.aac)

#### 0x28 Unknown Profile

| kbps     | bits     | chan     | rate     |  profile (payload)                    |
|---------:|---------:|:--------:|---------:|:--------------------------------------|
|        8 |       16 |        1 |    11025 |  0x28  Unknown Profile      (1 ADTS)  |
|        8 |       16 |        1 |    16000 |  0x28  Unknown Profile      (1 ADTS)  |
|       12 |       16 |        1 |    11025 |  0x28  Unknown Profile      (1 ADTS)  |
|       12 |       16 |        1 |    16000 |  0x28  Unknown Profile      (1 ADTS)  |
|       16 |       16 |        1 |    11025 |  0x28  Unknown Profile      (1 ADTS)  |
|       16 |       16 |        1 |    16000 |  0x28  Unknown Profile      (1 ADTS)  |
|       16 |       16 |        2 |    11025 |  0x28  Unknown Profile      (1 ADTS)  |
|       16 |       16 |        2 |    16000 |  0x28  Unknown Profile      (1 ADTS)  |
|       24 |       16 |        1 |    16000 |  0x28  Unknown Profile      (1 ADTS)  |
|       24 |       16 |        1 |    22050 |  0x28  Unknown Profile      (1 ADTS)  |
|       24 |       16 |        1 |    24000 |  0x28  Unknown Profile      (1 ADTS)  |
|       24 |       16 |        2 |    16000 |  0x28  Unknown Profile      (1 ADTS)  |
|       32 |       16 |        1 |    16000 |  0x28  Unknown Profile      (1 ADTS)  |
|       32 |       16 |        1 |    22050 |  0x28  Unknown Profile      (1 ADTS)  |
|       32 |       16 |        2 |    16000 |  0x28  Unknown Profile      (1 ADTS)  |
|       32 |       16 |        2 |    22050 |  0x28  Unknown Profile      (1 ADTS)  |
|       32 |       16 |        2 |    24000 |  0x28  Unknown Profile      (1 ADTS)  |

#### 0x29 AAC Profile L2

| kbps     | bits     | chan     | rate     |  profile (payload)                    |
|---------:|---------:|:--------:|---------:|:--------------------------------------|
|       32 |       16 |        1 |    24000 |  0x29  AAC Profile L2       (1 ADTS)  |
|       48 |       16 |        1 |    32000 |  0x29  AAC Profile L2       (1 ADTS)  |
|       48 |       16 |        1 |    44100 |  0x29  AAC Profile L2       (1 ADTS)  |
|       48 |       16 |        1 |    48000 |  0x29  AAC Profile L2       (1 ADTS)  |
|       48 |       16 |        2 |    32000 |  0x29  AAC Profile L2       (1 ADTS)  |
|       64 |       16 |        1 |    32000 |  0x29  AAC Profile L2       (1 ADTS)  |
|       64 |       16 |        1 |    44100 |  0x29  AAC Profile L2       (1 ADTS)  |
|       64 |       16 |        1 |    48000 |  0x29  AAC Profile L2       (1 ADTS)  |
|       64 |       16 |        2 |    32000 |  0x29  AAC Profile L2       (1 ADTS)  |
|       96 |       16 |        1 |    32000 |  0x29  AAC Profile L2       (1 ADTS)  |
|       96 |       16 |        1 |    44100 |  0x29  AAC Profile L2       (1 ADTS)  |
|       96 |       16 |        1 |    48000 |  0x29  AAC Profile L2       (1 ADTS)  |
|       96 |       16 |        2 |    32000 |  0x29  AAC Profile L2       (1 ADTS)  |
|       96 |       16 |        2 |    44100 |  0x29  AAC Profile L2       (1 ADTS)  |
|       96 |       16 |        2 |    48000 |  0x29  AAC Profile L2       (1 ADTS)  |
|      128 |       16 |        1 |    32000 |  0x29  AAC Profile L2       (1 ADTS)  |
|      128 |       16 |        1 |    44100 |  0x29  AAC Profile L2       (1 ADTS)  |
|      128 |       16 |        1 |    48000 |  0x29  AAC Profile L2       (1 ADTS)  |
|      128 |       16 |        2 |    32000 |  0x29  AAC Profile L2       (1 ADTS)  |
|      128 |       16 |        2 |    44100 |  0x29  AAC Profile L2       (1 ADTS)  |
|      128 |       16 |        2 |    48000 |  0x29  AAC Profile L2       (1 ADTS)  |
|      160 |       16 |        1 |    44100 |  0x29  AAC Profile L2       (1 ADTS)  |
|      160 |       16 |        1 |    48000 |  0x29  AAC Profile L2       (1 ADTS)  |
|      160 |       16 |        2 |    44100 |  0x29  AAC Profile L2       (1 ADTS)  |
|      160 |       16 |        2 |    48000 |  0x29  AAC Profile L2       (1 ADTS)  |
|      192 |       16 |        1 |    44100 |  0x29  AAC Profile L2       (1 ADTS)  |
|      192 |       16 |        1 |    48000 |  0x29  AAC Profile L2       (1 ADTS)  |
|      192 |       16 |        2 |    32000 |  0x29  AAC Profile L2       (1 ADTS)  |
|      192 |       16 |        2 |    44100 |  0x29  AAC Profile L2       (1 ADTS)  |
|      192 |       16 |        2 |    48000 |  0x29  AAC Profile L2       (1 ADTS)  |
|      256 |       16 |        2 |    32000 |  0x29  AAC Profile L2       (1 ADTS)  |
|      256 |       16 |        2 |    44100 |  0x29  AAC Profile L2       (1 ADTS)  |
|      256 |       16 |        2 |    48000 |  0x29  AAC Profile L2       (1 ADTS)  |
|      320 |       16 |        2 |    32000 |  0x29  AAC Profile L2       (1 ADTS)  |
|      320 |       16 |        2 |    44100 |  0x29  AAC Profile L2       (1 ADTS)  |
|      320 |       16 |        2 |    48000 |  0x29  AAC Profile L2       (1 ADTS)  |

#### 0x2A AAC Profile L4

| kbps     | bits     | chan     | rate     |  profile (payload)                    |
|---------:|---------:|:--------:|---------:|:--------------------------------------|
|      128 |       16 |        6 |    32000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      128 |       16 |        6 |    44100 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      128 |       16 |        6 |    48000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      192 |       16 |        6 |    32000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      192 |       16 |        6 |    44100 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      192 |       16 |        6 |    48000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      256 |       16 |        6 |    32000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      256 |       16 |        6 |    44100 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      256 |       16 |        6 |    48000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      320 |       16 |        6 |    32000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      320 |       16 |        6 |    44100 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      320 |       16 |        6 |    48000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      480 |       16 |        6 |    32000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      480 |       16 |        6 |    44100 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      480 |       16 |        6 |    48000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      512 |       16 |        6 |    32000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      512 |       16 |        6 |    44100 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      512 |       16 |        6 |    48000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      576 |       16 |        6 |    44100 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      576 |       16 |        6 |    48000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      640 |       16 |        6 |    32000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      640 |       16 |        6 |    44100 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      640 |       16 |        6 |    48000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      720 |       16 |        6 |    32000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      720 |       16 |        6 |    44100 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      720 |       16 |        6 |    48000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      768 |       16 |        6 |    44100 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      768 |       16 |        6 |    48000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      960 |       16 |        6 |    44100 |  0x2A  AAC Profile L4       (1 ADTS)  |
|      960 |       16 |        6 |    48000 |  0x2A  AAC Profile L4       (1 ADTS)  |
|     1152 |       16 |        6 |    44100 |  0x2A  AAC Profile L4       (1 ADTS)  |
|     1152 |       16 |        6 |    48000 |  0x2A  AAC Profile L4       (1 ADTS)  |

#### 0x2B AAC Profile L5

| kbps     | bits     | chan     | rate     |  profile (payload)                    |
|---------:|---------:|:--------:|---------:|:--------------------------------------|
|      320 |       16 |        2 |    96000 |  0x2B  AAC Profile L5       (1 ADTS)  |

#### 0x50 Unknown Profile

| kbps     | bits     | chan     | rate     |  profile (payload)                    |
|---------:|---------:|:--------:|---------:|:--------------------------------------|
|      256 |       16 |        8 |    32000 |  0x50  Unknown Profile      (1 ADTS)  |
|      256 |       16 |        8 |    44100 |  0x50  Unknown Profile      (1 ADTS)  |
|      256 |       16 |        8 |    48000 |  0x50  Unknown Profile      (1 ADTS)  |
|      320 |       16 |        8 |    32000 |  0x50  Unknown Profile      (1 ADTS)  |
|      320 |       16 |        8 |    44100 |  0x50  Unknown Profile      (1 ADTS)  |
|      320 |       16 |        8 |    48000 |  0x50  Unknown Profile      (1 ADTS)  |
|      480 |       16 |        8 |    32000 |  0x50  Unknown Profile      (1 ADTS)  |
|      480 |       16 |        8 |    44100 |  0x50  Unknown Profile      (1 ADTS)  |
|      480 |       16 |        8 |    48000 |  0x50  Unknown Profile      (1 ADTS)  |
|      512 |       16 |        8 |    32000 |  0x50  Unknown Profile      (1 ADTS)  |
|      512 |       16 |        8 |    44100 |  0x50  Unknown Profile      (1 ADTS)  |
|      512 |       16 |        8 |    48000 |  0x50  Unknown Profile      (1 ADTS)  |
|      640 |       16 |        8 |    32000 |  0x50  Unknown Profile      (1 ADTS)  |
|      640 |       16 |        8 |    44100 |  0x50  Unknown Profile      (1 ADTS)  |
|      640 |       16 |        8 |    48000 |  0x50  Unknown Profile      (1 ADTS)  |
|      720 |       16 |        8 |    32000 |  0x50  Unknown Profile      (1 ADTS)  |
|      720 |       16 |        8 |    44100 |  0x50  Unknown Profile      (1 ADTS)  |
|      720 |       16 |        8 |    48000 |  0x50  Unknown Profile      (1 ADTS)  |

----------------------------------------

## FLAC audio encoder

| kbps     | bits     | chan     | rate     |  format                           |
|---------:|---------:|:--------:|---------:|:----------------------------------|
|        1 |        8 |        1 |    44100 |  MFAudioFormat_FLAC               |
|        1 |        8 |        1 |    48000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        1 |    88200 |  MFAudioFormat_FLAC               |
|        1 |        8 |        1 |    96000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        1 |   176400 |  MFAudioFormat_FLAC               |
|        1 |        8 |        1 |   192000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        2 |    44100 |  MFAudioFormat_FLAC               |
|        1 |        8 |        2 |    48000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        2 |    88200 |  MFAudioFormat_FLAC               |
|        1 |        8 |        2 |    96000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        2 |   176400 |  MFAudioFormat_FLAC               |
|        1 |        8 |        2 |   192000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        3 |    44100 |  MFAudioFormat_FLAC               |
|        1 |        8 |        3 |    48000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        3 |    88200 |  MFAudioFormat_FLAC               |
|        1 |        8 |        3 |    96000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        3 |   176400 |  MFAudioFormat_FLAC               |
|        1 |        8 |        3 |   192000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        4 |    44100 |  MFAudioFormat_FLAC               |
|        1 |        8 |        4 |    48000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        4 |    88200 |  MFAudioFormat_FLAC               |
|        1 |        8 |        4 |    96000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        4 |   176400 |  MFAudioFormat_FLAC               |
|        1 |        8 |        4 |   192000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        5 |    44100 |  MFAudioFormat_FLAC               |
|        1 |        8 |        5 |    48000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        5 |    88200 |  MFAudioFormat_FLAC               |
|        1 |        8 |        5 |    96000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        5 |   176400 |  MFAudioFormat_FLAC               |
|        1 |        8 |        5 |   192000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        6 |    44100 |  MFAudioFormat_FLAC               |
|        1 |        8 |        6 |    48000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        6 |    88200 |  MFAudioFormat_FLAC               |
|        1 |        8 |        6 |    96000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        6 |   176400 |  MFAudioFormat_FLAC               |
|        1 |        8 |        6 |   192000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        7 |    44100 |  MFAudioFormat_FLAC               |
|        1 |        8 |        7 |    48000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        7 |    88200 |  MFAudioFormat_FLAC               |
|        1 |        8 |        7 |    96000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        7 |   176400 |  MFAudioFormat_FLAC               |
|        1 |        8 |        7 |   192000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        8 |    44100 |  MFAudioFormat_FLAC               |
|        1 |        8 |        8 |    48000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        8 |    88200 |  MFAudioFormat_FLAC               |
|        1 |        8 |        8 |    96000 |  MFAudioFormat_FLAC               |
|        1 |        8 |        8 |   176400 |  MFAudioFormat_FLAC               |
|        1 |        8 |        8 |   192000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        1 |    44100 |  MFAudioFormat_FLAC               |
|        1 |       16 |        1 |    48000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        1 |    88200 |  MFAudioFormat_FLAC               |
|        1 |       16 |        1 |    96000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        1 |   176400 |  MFAudioFormat_FLAC               |
|        1 |       16 |        1 |   192000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        2 |    44100 |  MFAudioFormat_FLAC               |
|        1 |       16 |        2 |    48000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        2 |    88200 |  MFAudioFormat_FLAC               |
|        1 |       16 |        2 |    96000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        2 |   176400 |  MFAudioFormat_FLAC               |
|        1 |       16 |        2 |   192000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        3 |    44100 |  MFAudioFormat_FLAC               |
|        1 |       16 |        3 |    48000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        3 |    88200 |  MFAudioFormat_FLAC               |
|        1 |       16 |        3 |    96000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        3 |   176400 |  MFAudioFormat_FLAC               |
|        1 |       16 |        3 |   192000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        4 |    44100 |  MFAudioFormat_FLAC               |
|        1 |       16 |        4 |    48000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        4 |    88200 |  MFAudioFormat_FLAC               |
|        1 |       16 |        4 |    96000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        4 |   176400 |  MFAudioFormat_FLAC               |
|        1 |       16 |        4 |   192000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        5 |    44100 |  MFAudioFormat_FLAC               |
|        1 |       16 |        5 |    48000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        5 |    88200 |  MFAudioFormat_FLAC               |
|        1 |       16 |        5 |    96000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        5 |   176400 |  MFAudioFormat_FLAC               |
|        1 |       16 |        5 |   192000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        6 |    44100 |  MFAudioFormat_FLAC               |
|        1 |       16 |        6 |    48000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        6 |    88200 |  MFAudioFormat_FLAC               |
|        1 |       16 |        6 |    96000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        6 |   176400 |  MFAudioFormat_FLAC               |
|        1 |       16 |        6 |   192000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        7 |    44100 |  MFAudioFormat_FLAC               |
|        1 |       16 |        7 |    48000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        7 |    88200 |  MFAudioFormat_FLAC               |
|        1 |       16 |        7 |    96000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        7 |   176400 |  MFAudioFormat_FLAC               |
|        1 |       16 |        7 |   192000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        8 |    44100 |  MFAudioFormat_FLAC               |
|        1 |       16 |        8 |    48000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        8 |    88200 |  MFAudioFormat_FLAC               |
|        1 |       16 |        8 |    96000 |  MFAudioFormat_FLAC               |
|        1 |       16 |        8 |   176400 |  MFAudioFormat_FLAC               |
|        1 |       16 |        8 |   192000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        1 |    44100 |  MFAudioFormat_FLAC               |
|        1 |       24 |        1 |    48000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        1 |    88200 |  MFAudioFormat_FLAC               |
|        1 |       24 |        1 |    96000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        1 |   176400 |  MFAudioFormat_FLAC               |
|        1 |       24 |        1 |   192000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        2 |    44100 |  MFAudioFormat_FLAC               |
|        1 |       24 |        2 |    48000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        2 |    88200 |  MFAudioFormat_FLAC               |
|        1 |       24 |        2 |    96000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        2 |   176400 |  MFAudioFormat_FLAC               |
|        1 |       24 |        2 |   192000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        3 |    44100 |  MFAudioFormat_FLAC               |
|        1 |       24 |        3 |    48000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        3 |    88200 |  MFAudioFormat_FLAC               |
|        1 |       24 |        3 |    96000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        3 |   176400 |  MFAudioFormat_FLAC               |
|        1 |       24 |        3 |   192000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        4 |    44100 |  MFAudioFormat_FLAC               |
|        1 |       24 |        4 |    48000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        4 |    88200 |  MFAudioFormat_FLAC               |
|        1 |       24 |        4 |    96000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        4 |   176400 |  MFAudioFormat_FLAC               |
|        1 |       24 |        4 |   192000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        5 |    44100 |  MFAudioFormat_FLAC               |
|        1 |       24 |        5 |    48000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        5 |    88200 |  MFAudioFormat_FLAC               |
|        1 |       24 |        5 |    96000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        5 |   176400 |  MFAudioFormat_FLAC               |
|        1 |       24 |        5 |   192000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        6 |    44100 |  MFAudioFormat_FLAC               |
|        1 |       24 |        6 |    48000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        6 |    88200 |  MFAudioFormat_FLAC               |
|        1 |       24 |        6 |    96000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        6 |   176400 |  MFAudioFormat_FLAC               |
|        1 |       24 |        6 |   192000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        7 |    44100 |  MFAudioFormat_FLAC               |
|        1 |       24 |        7 |    48000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        7 |    88200 |  MFAudioFormat_FLAC               |
|        1 |       24 |        7 |    96000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        7 |   176400 |  MFAudioFormat_FLAC               |
|        1 |       24 |        7 |   192000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        8 |    44100 |  MFAudioFormat_FLAC               |
|        1 |       24 |        8 |    48000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        8 |    88200 |  MFAudioFormat_FLAC               |
|        1 |       24 |        8 |    96000 |  MFAudioFormat_FLAC               |
|        1 |       24 |        8 |   176400 |  MFAudioFormat_FLAC               |
|        1 |       24 |        8 |   192000 |  MFAudioFormat_FLAC               |

----------------------------------------

## MPEG Layer 2 audio encoder

| kbps     | bits     | chan     | rate     |  format                           |
|---------:|---------:|:--------:|---------:|:----------------------------------|
|      160 |        0 |        1 |    16000 |  MFAudioFormat_MPEG               |
|      160 |        0 |        1 |    22050 |  MFAudioFormat_MPEG               |
|      160 |        0 |        1 |    24000 |  MFAudioFormat_MPEG               |
|      160 |        0 |        2 |    16000 |  MFAudioFormat_MPEG               |
|      160 |        0 |        2 |    22050 |  MFAudioFormat_MPEG               |
|      160 |        0 |        2 |    24000 |  MFAudioFormat_MPEG               |
|      192 |        0 |        1 |    32000 |  MFAudioFormat_MPEG               |
|      192 |        0 |        1 |    44100 |  MFAudioFormat_MPEG               |
|      192 |        0 |        1 |    48000 |  MFAudioFormat_MPEG               |
|      224 |        0 |        2 |    32000 |  MFAudioFormat_MPEG               |
|      224 |        0 |        2 |    44100 |  MFAudioFormat_MPEG               |
|      224 |        0 |        2 |    48000 |  MFAudioFormat_MPEG               |

----------------------------------------

## MPEG Layer 3 audio encoder

| kbps     | bits     | chan     | rate     |  format                           |
|---------:|---------:|:--------:|---------:|:----------------------------------|
|        8 |        0 |        1 |     8000 |  MFAudioFormat_MP3                |
|        8 |        0 |        1 |    11025 |  MFAudioFormat_MP3                |
|        8 |        0 |        1 |    12000 |  MFAudioFormat_MP3                |
|       16 |        0 |        1 |     8000 |  MFAudioFormat_MP3                |
|       16 |        0 |        1 |    11025 |  MFAudioFormat_MP3                |
|       16 |        0 |        1 |    12000 |  MFAudioFormat_MP3                |
|       16 |        0 |        1 |    16000 |  MFAudioFormat_MP3                |
|       18 |        0 |        1 |    11025 |  MFAudioFormat_MP3                |
|       18 |        0 |        1 |    12000 |  MFAudioFormat_MP3                |
|       18 |        0 |        1 |    16000 |  MFAudioFormat_MP3                |
|       18 |        0 |        2 |     8000 |  MFAudioFormat_MP3                |
|       18 |        0 |        2 |    11025 |  MFAudioFormat_MP3                |
|       18 |        0 |        2 |    12000 |  MFAudioFormat_MP3                |
|       20 |        0 |        1 |    11025 |  MFAudioFormat_MP3                |
|       20 |        0 |        1 |    12000 |  MFAudioFormat_MP3                |
|       20 |        0 |        1 |    16000 |  MFAudioFormat_MP3                |
|       20 |        0 |        2 |     8000 |  MFAudioFormat_MP3                |
|       20 |        0 |        2 |    11025 |  MFAudioFormat_MP3                |
|       20 |        0 |        2 |    12000 |  MFAudioFormat_MP3                |
|       24 |        0 |        1 |    16000 |  MFAudioFormat_MP3                |
|       24 |        0 |        1 |    22050 |  MFAudioFormat_MP3                |
|       24 |        0 |        1 |    24000 |  MFAudioFormat_MP3                |
|       24 |        0 |        2 |     8000 |  MFAudioFormat_MP3                |
|       24 |        0 |        2 |    11025 |  MFAudioFormat_MP3                |
|       24 |        0 |        2 |    12000 |  MFAudioFormat_MP3                |
|       32 |        0 |        1 |    16000 |  MFAudioFormat_MP3                |
|       32 |        0 |        1 |    22050 |  MFAudioFormat_MP3                |
|       32 |        0 |        1 |    24000 |  MFAudioFormat_MP3                |
|       32 |        0 |        2 |     8000 |  MFAudioFormat_MP3                |
|       32 |        0 |        2 |    11025 |  MFAudioFormat_MP3                |
|       32 |        0 |        2 |    12000 |  MFAudioFormat_MP3                |
|       32 |        0 |        2 |    16000 |  MFAudioFormat_MP3                |
|       32 |        0 |        2 |    22050 |  MFAudioFormat_MP3                |
|       32 |        0 |        2 |    24000 |  MFAudioFormat_MP3                |
|       40 |        0 |        1 |    16000 |  MFAudioFormat_MP3                |
|       40 |        0 |        1 |    22050 |  MFAudioFormat_MP3                |
|       40 |        0 |        1 |    24000 |  MFAudioFormat_MP3                |
|       40 |        0 |        2 |    16000 |  MFAudioFormat_MP3                |
|       40 |        0 |        2 |    22050 |  MFAudioFormat_MP3                |
|       40 |        0 |        2 |    24000 |  MFAudioFormat_MP3                |
|       48 |        0 |        1 |    16000 |  MFAudioFormat_MP3                |
|       48 |        0 |        1 |    22050 |  MFAudioFormat_MP3                |
|       48 |        0 |        1 |    24000 |  MFAudioFormat_MP3                |
|       48 |        0 |        1 |    32000 |  MFAudioFormat_MP3                |
|       48 |        0 |        1 |    44100 |  MFAudioFormat_MP3                |
|       48 |        0 |        1 |    48000 |  MFAudioFormat_MP3                |
|       48 |        0 |        2 |    16000 |  MFAudioFormat_MP3                |
|       48 |        0 |        2 |    22050 |  MFAudioFormat_MP3                |
|       48 |        0 |        2 |    24000 |  MFAudioFormat_MP3                |
|       56 |        0 |        1 |    32000 |  MFAudioFormat_MP3                |
|       56 |        0 |        1 |    44100 |  MFAudioFormat_MP3                |
|       56 |        0 |        1 |    48000 |  MFAudioFormat_MP3                |
|       56 |        0 |        2 |    16000 |  MFAudioFormat_MP3                |
|       56 |        0 |        2 |    22050 |  MFAudioFormat_MP3                |
|       56 |        0 |        2 |    24000 |  MFAudioFormat_MP3                |
|       64 |        0 |        1 |    32000 |  MFAudioFormat_MP3                |
|       64 |        0 |        1 |    44100 |  MFAudioFormat_MP3                |
|       64 |        0 |        1 |    48000 |  MFAudioFormat_MP3                |
|       64 |        0 |        2 |    16000 |  MFAudioFormat_MP3                |
|       64 |        0 |        2 |    22050 |  MFAudioFormat_MP3                |
|       64 |        0 |        2 |    24000 |  MFAudioFormat_MP3                |
|       80 |        0 |        1 |    32000 |  MFAudioFormat_MP3                |
|       80 |        0 |        1 |    44100 |  MFAudioFormat_MP3                |
|       80 |        0 |        1 |    48000 |  MFAudioFormat_MP3                |
|       80 |        0 |        2 |    16000 |  MFAudioFormat_MP3                |
|       80 |        0 |        2 |    22050 |  MFAudioFormat_MP3                |
|       80 |        0 |        2 |    24000 |  MFAudioFormat_MP3                |
|       96 |        0 |        1 |    32000 |  MFAudioFormat_MP3                |
|       96 |        0 |        1 |    44100 |  MFAudioFormat_MP3                |
|       96 |        0 |        1 |    48000 |  MFAudioFormat_MP3                |
|       96 |        0 |        2 |    32000 |  MFAudioFormat_MP3                |
|       96 |        0 |        2 |    44100 |  MFAudioFormat_MP3                |
|       96 |        0 |        2 |    48000 |  MFAudioFormat_MP3                |
|      112 |        0 |        1 |    32000 |  MFAudioFormat_MP3                |
|      112 |        0 |        1 |    44100 |  MFAudioFormat_MP3                |
|      112 |        0 |        1 |    48000 |  MFAudioFormat_MP3                |
|      112 |        0 |        2 |    32000 |  MFAudioFormat_MP3                |
|      112 |        0 |        2 |    44100 |  MFAudioFormat_MP3                |
|      112 |        0 |        2 |    48000 |  MFAudioFormat_MP3                |
|      128 |        0 |        1 |    32000 |  MFAudioFormat_MP3                |
|      128 |        0 |        1 |    44100 |  MFAudioFormat_MP3                |
|      128 |        0 |        1 |    48000 |  MFAudioFormat_MP3                |
|      128 |        0 |        2 |    32000 |  MFAudioFormat_MP3                |
|      128 |        0 |        2 |    44100 |  MFAudioFormat_MP3                |
|      128 |        0 |        2 |    48000 |  MFAudioFormat_MP3                |
|      160 |        0 |        2 |    32000 |  MFAudioFormat_MP3                |
|      160 |        0 |        2 |    44100 |  MFAudioFormat_MP3                |
|      160 |        0 |        2 |    48000 |  MFAudioFormat_MP3                |
|      192 |        0 |        2 |    32000 |  MFAudioFormat_MP3                |
|      192 |        0 |        2 |    44100 |  MFAudioFormat_MP3                |
|      192 |        0 |        2 |    48000 |  MFAudioFormat_MP3                |
|      224 |        0 |        2 |    32000 |  MFAudioFormat_MP3                |
|      224 |        0 |        2 |    44100 |  MFAudioFormat_MP3                |
|      224 |        0 |        2 |    48000 |  MFAudioFormat_MP3                |
|      256 |        0 |        2 |    32000 |  MFAudioFormat_MP3                |
|      256 |        0 |        2 |    44100 |  MFAudioFormat_MP3                |
|      256 |        0 |        2 |    48000 |  MFAudioFormat_MP3                |
|      320 |        0 |        2 |    32000 |  MFAudioFormat_MP3                |
|      320 |        0 |        2 |    44100 |  MFAudioFormat_MP3                |
|      320 |        0 |        2 |    48000 |  MFAudioFormat_MP3                |

----------------------------------------

## WMA 8 audio encoder

| kbps     | bits     | chan     | rate     |  format                           |
|---------:|---------:|:--------:|---------:|:----------------------------------|
|        0 |       16 |        1 |     8000 |  MFAudioFormat_WMAudioV8          |
|        5 |       16 |        1 |     8000 |  MFAudioFormat_WMAudioV8          |
|        5 |       16 |        1 |     8000 |  MFAudioFormat_WMAudioV8          |
|        6 |       16 |        1 |     8000 |  MFAudioFormat_WMAudioV8          |
|        6 |       16 |        1 |     8000 |  MFAudioFormat_WMAudioV8          |
|        8 |       16 |        1 |     8000 |  MFAudioFormat_WMAudioV8          |
|        8 |       16 |        1 |     8000 |  MFAudioFormat_WMAudioV8          |
|        8 |       16 |        1 |    11025 |  MFAudioFormat_WMAudioV8          |
|        8 |       16 |        1 |    11025 |  MFAudioFormat_WMAudioV8          |
|       10 |       16 |        1 |    11025 |  MFAudioFormat_WMAudioV8          |
|       10 |       16 |        1 |    11025 |  MFAudioFormat_WMAudioV8          |
|       10 |       16 |        1 |    16000 |  MFAudioFormat_WMAudioV8          |
|       12 |       16 |        1 |    16000 |  MFAudioFormat_WMAudioV8          |
|       12 |       16 |        2 |     8000 |  MFAudioFormat_WMAudioV8          |
|       12 |       16 |        2 |     8000 |  MFAudioFormat_WMAudioV8          |
|       16 |       16 |        1 |    16000 |  MFAudioFormat_WMAudioV8          |
|       16 |       16 |        1 |    22050 |  MFAudioFormat_WMAudioV8          |
|       16 |       16 |        1 |    22050 |  MFAudioFormat_WMAudioV8          |
|       16 |       16 |        2 |    16000 |  MFAudioFormat_WMAudioV8          |
|       20 |       16 |        1 |    22050 |  MFAudioFormat_WMAudioV8          |
|       20 |       16 |        1 |    22050 |  MFAudioFormat_WMAudioV8          |
|       20 |       16 |        1 |    32000 |  MFAudioFormat_WMAudioV8          |
|       20 |       16 |        1 |    32000 |  MFAudioFormat_WMAudioV8          |
|       20 |       16 |        1 |    44100 |  MFAudioFormat_WMAudioV8          |
|       20 |       16 |        1 |    44100 |  MFAudioFormat_WMAudioV8          |
|       20 |       16 |        2 |    16000 |  MFAudioFormat_WMAudioV8          |
|       20 |       16 |        2 |    22050 |  MFAudioFormat_WMAudioV8          |
|       20 |       16 |        2 |    22050 |  MFAudioFormat_WMAudioV8          |
|       22 |       16 |        2 |    22050 |  MFAudioFormat_WMAudioV8          |
|       22 |       16 |        2 |    22050 |  MFAudioFormat_WMAudioV8          |
|       24 |       16 |        2 |    32000 |  MFAudioFormat_WMAudioV8          |
|       24 |       16 |        2 |    32000 |  MFAudioFormat_WMAudioV8          |
|       31 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|       31 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|       32 |       16 |        1 |    44100 |  MFAudioFormat_WMAudioV8          |
|       32 |       16 |        1 |    44100 |  MFAudioFormat_WMAudioV8          |
|       32 |       16 |        2 |    22050 |  MFAudioFormat_WMAudioV8          |
|       32 |       16 |        2 |    22050 |  MFAudioFormat_WMAudioV8          |
|       32 |       16 |        2 |    32000 |  MFAudioFormat_WMAudioV8          |
|       32 |       16 |        2 |    32000 |  MFAudioFormat_WMAudioV8          |
|       40 |       16 |        2 |    32000 |  MFAudioFormat_WMAudioV8          |
|       40 |       16 |        2 |    32000 |  MFAudioFormat_WMAudioV8          |
|       48 |       16 |        1 |    44100 |  MFAudioFormat_WMAudioV8          |
|       48 |       16 |        1 |    44100 |  MFAudioFormat_WMAudioV8          |
|       48 |       16 |        2 |    32000 |  MFAudioFormat_WMAudioV8          |
|       48 |       16 |        2 |    32000 |  MFAudioFormat_WMAudioV8          |
|       48 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|       48 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|       64 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|       64 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|       64 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV8          |
|       64 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV8          |
|       80 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|       80 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|       96 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|       96 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|       96 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV8          |
|       96 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV8          |
|      128 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|      128 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|      128 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV8          |
|      128 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV8          |
|      160 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|      160 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|      160 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV8          |
|      160 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV8          |
|      192 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|      192 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|      192 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV8          |
|      192 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV8          |
|      256 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|      256 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|      320 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |
|      320 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV8          |

----------------------------------------

## WMA 9 audio encoder

| kbps     | bits     | chan     | rate     |  format                           |
|---------:|---------:|:--------:|---------:|:----------------------------------|
|       32 |       16 |        2 |    32000 |  MFAudioFormat_WMAudioV9          |
|       32 |       16 |        2 |    32000 |  MFAudioFormat_WMAudioV9          |
|       48 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|       48 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|       48 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|       48 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|       64 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|       64 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|       64 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|       64 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|       80 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|       80 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|       80 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|       80 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|       96 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|       96 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|       96 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|       96 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      128 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      128 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      128 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      128 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      128 |       16 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      128 |       16 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      128 |       16 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      128 |       16 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      128 |       16 |        8 |    48000 |  MFAudioFormat_WMAudioV9          |
|      128 |       16 |        8 |    48000 |  MFAudioFormat_WMAudioV9          |
|      128 |       24 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      128 |       24 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      128 |       24 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      128 |       24 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      128 |       24 |        2 |    88200 |  MFAudioFormat_WMAudioV9          |
|      128 |       24 |        2 |    88200 |  MFAudioFormat_WMAudioV9          |
|      128 |       24 |        2 |    96000 |  MFAudioFormat_WMAudioV9          |
|      128 |       24 |        2 |    96000 |  MFAudioFormat_WMAudioV9          |
|      128 |       24 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      128 |       24 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      128 |       24 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      128 |       24 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      128 |       24 |        6 |    96000 |  MFAudioFormat_WMAudioV9          |
|      128 |       24 |        6 |    96000 |  MFAudioFormat_WMAudioV9          |
|      160 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      160 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      160 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      160 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      160 |       16 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      160 |       16 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      160 |       16 |        8 |    48000 |  MFAudioFormat_WMAudioV9          |
|      160 |       16 |        8 |    48000 |  MFAudioFormat_WMAudioV9          |
|      192 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      192 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      192 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      192 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      192 |       16 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      192 |       16 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      192 |       16 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      192 |       16 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      192 |       24 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      192 |       24 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      192 |       24 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      192 |       24 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      192 |       24 |        2 |    88200 |  MFAudioFormat_WMAudioV9          |
|      192 |       24 |        2 |    88200 |  MFAudioFormat_WMAudioV9          |
|      192 |       24 |        2 |    96000 |  MFAudioFormat_WMAudioV9          |
|      192 |       24 |        2 |    96000 |  MFAudioFormat_WMAudioV9          |
|      192 |       24 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      192 |       24 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      192 |       24 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      192 |       24 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      192 |       24 |        6 |    96000 |  MFAudioFormat_WMAudioV9          |
|      192 |       24 |        6 |    96000 |  MFAudioFormat_WMAudioV9          |
|      256 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      256 |       16 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      256 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      256 |       16 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      256 |       16 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      256 |       16 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      256 |       16 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      256 |       16 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      256 |       24 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      256 |       24 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      256 |       24 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      256 |       24 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      256 |       24 |        2 |    88200 |  MFAudioFormat_WMAudioV9          |
|      256 |       24 |        2 |    88200 |  MFAudioFormat_WMAudioV9          |
|      256 |       24 |        2 |    96000 |  MFAudioFormat_WMAudioV9          |
|      256 |       24 |        2 |    96000 |  MFAudioFormat_WMAudioV9          |
|      256 |       24 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      256 |       24 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      256 |       24 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      256 |       24 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      256 |       24 |        6 |    96000 |  MFAudioFormat_WMAudioV9          |
|      256 |       24 |        6 |    96000 |  MFAudioFormat_WMAudioV9          |
|      384 |       16 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      384 |       16 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      384 |       16 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      384 |       16 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      384 |       24 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      384 |       24 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      384 |       24 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      384 |       24 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      384 |       24 |        2 |    88200 |  MFAudioFormat_WMAudioV9          |
|      384 |       24 |        2 |    88200 |  MFAudioFormat_WMAudioV9          |
|      384 |       24 |        2 |    96000 |  MFAudioFormat_WMAudioV9          |
|      384 |       24 |        2 |    96000 |  MFAudioFormat_WMAudioV9          |
|      384 |       24 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      384 |       24 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      384 |       24 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      384 |       24 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      384 |       24 |        6 |    96000 |  MFAudioFormat_WMAudioV9          |
|      384 |       24 |        6 |    96000 |  MFAudioFormat_WMAudioV9          |
|      384 |       24 |        8 |    48000 |  MFAudioFormat_WMAudioV9          |
|      384 |       24 |        8 |    48000 |  MFAudioFormat_WMAudioV9          |
|      440 |       16 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      440 |       16 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      440 |       16 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      440 |       16 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      440 |       24 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      440 |       24 |        2 |    44100 |  MFAudioFormat_WMAudioV9          |
|      440 |       24 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      440 |       24 |        2 |    48000 |  MFAudioFormat_WMAudioV9          |
|      440 |       24 |        2 |    88200 |  MFAudioFormat_WMAudioV9          |
|      440 |       24 |        2 |    88200 |  MFAudioFormat_WMAudioV9          |
|      440 |       24 |        2 |    96000 |  MFAudioFormat_WMAudioV9          |
|      440 |       24 |        2 |    96000 |  MFAudioFormat_WMAudioV9          |
|      440 |       24 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      440 |       24 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      440 |       24 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      440 |       24 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      440 |       24 |        6 |    96000 |  MFAudioFormat_WMAudioV9          |
|      440 |       24 |        6 |    96000 |  MFAudioFormat_WMAudioV9          |
|      640 |       24 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      640 |       24 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      640 |       24 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      640 |       24 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      640 |       24 |        6 |    96000 |  MFAudioFormat_WMAudioV9          |
|      640 |       24 |        6 |    96000 |  MFAudioFormat_WMAudioV9          |
|      768 |       24 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      768 |       24 |        6 |    44100 |  MFAudioFormat_WMAudioV9          |
|      768 |       24 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      768 |       24 |        6 |    48000 |  MFAudioFormat_WMAudioV9          |
|      768 |       24 |        6 |    96000 |  MFAudioFormat_WMAudioV9          |
|      768 |       24 |        6 |    96000 |  MFAudioFormat_WMAudioV9          |
|      768 |       24 |        8 |    48000 |  MFAudioFormat_WMAudioV9          |
|      768 |       24 |        8 |    48000 |  MFAudioFormat_WMAudioV9          |
|      768 |       24 |        8 |    96000 |  MFAudioFormat_WMAudioV9          |
|      768 |       24 |        8 |    96000 |  MFAudioFormat_WMAudioV9          |

----------------------------------------

## WMA Lossless audio encoder

| kbps     | bits     | chan     | rate     |  format                           |
|---------:|---------:|:--------:|---------:|:----------------------------------|
|     1152 |       16 |        2 |    44100 |  MFAudioFormat_WMAudio_Lossless   |
|     1152 |       24 |        2 |    44100 |  MFAudioFormat_WMAudio_Lossless   |
|     1152 |       24 |        2 |    48000 |  MFAudioFormat_WMAudio_Lossless   |
|     1152 |       24 |        2 |    88200 |  MFAudioFormat_WMAudio_Lossless   |
|     1152 |       24 |        2 |    96000 |  MFAudioFormat_WMAudio_Lossless   |
|     1152 |       24 |        6 |    48000 |  MFAudioFormat_WMAudio_Lossless   |
|     1152 |       24 |        6 |    88200 |  MFAudioFormat_WMAudio_Lossless   |
|     1152 |       24 |        6 |    96000 |  MFAudioFormat_WMAudio_Lossless   |

----------------------------------------

## WMA Voice audio encoder

| kbps     | bits     | chan     | rate     |  format                           |
|---------:|---------:|:--------:|---------:|:----------------------------------|
|        4 |        0 |        1 |     8000 |  MFAudioFormat_MSP1               |
|        5 |        0 |        1 |     8000 |  MFAudioFormat_MSP1               |
|        8 |        0 |        1 |     8000 |  MFAudioFormat_MSP1               |
|       10 |        0 |        1 |    11025 |  MFAudioFormat_MSP1               |
|       12 |        0 |        1 |    16000 |  MFAudioFormat_MSP1               |
|       16 |        0 |        1 |    16000 |  MFAudioFormat_MSP1               |
|       20 |        0 |        1 |    22050 |  MFAudioFormat_MSP1               |

----------------------------------------
