import serial
import openai

key = "insert key here"
sConnection = serial.Serial()

def waitForArduino():
    while True:
        print('waiting')
        str = sConnection.readline()
        str = str.decode().strip()
        if str == "Requesting Pair":
            break
    sConnection.write(b'Paired\n')

def sendToArduino(sendStr):
    sendStr.replace('\"', "")
    sConnection.write((sendStr+'\n').encode())
    sConnection.write(b'Done\n')
    print('sent')

def receiveFromArduino():
    print('receiving')
    str = ""
    while True:
        nextline = sConnection.readline()
        nextline = nextline.decode().strip()
        if nextline == "Done":
            break
        str += nextline
    if str == "Done":
        raise ValueError("Prompt invalid")
    return str

def promptGPT(str):
    openai.api_key = key
    promptstr = "Please make a sentence to someone you are talking to using these words: " + str
    prompt = [{"role": "user", "content": promptstr}]
    response = openai.ChatCompletion.create(model="gpt-3.5-turbo", messages=prompt)
    result = response['choices'][0]['message']['content']
    return result
def program():
    sConnection.port = 'COM5'
    sConnection.baudrate = 19200
    sConnection.open()
    waitForArduino()
    prompt = receiveFromArduino()
    response = promptGPT(prompt)
    sendToArduino(response)
    sConnection.close()

if __name__ == '__main__':
    program()