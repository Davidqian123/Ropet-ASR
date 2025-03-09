from openai import OpenAI
client = OpenAI(api_key="your_api_key")

audio_file= open("6.wav", "rb")
transcription = client.audio.transcriptions.create(
    model="whisper-1", 
    file=audio_file,
    language="ja"
)

print(transcription.text)