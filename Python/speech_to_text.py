import json  
from os.path import join, dirname  
from watson_developer_cloud import SpeechToTextV1

# https://www.ibm.com/watson/developercloud/doc/speech-to-text/input.shtml
# http://www.ifreesite.com/unicode-ascii-ansi.htm

STT_Model = 'zh-CN_BroadbandModel'  
userName = 'USERNAME'  
passWord = 'PASSWORD'

speech_to_text = SpeechToTextV1(  
    username = userName,
    password = passWord,
    x_watson_learning_opt_out = False
)

print(json.dumps(speech_to_text.models(), indent=2))

with open(join(dirname(__file__), './resources/chinese.wav'), 'rb') as audio_file:  
    print(json.dumps(speech_to_text.recognize(
        audio_file, content_type='audio/wav', model= STT_Model, timestamps=True), indent=2))