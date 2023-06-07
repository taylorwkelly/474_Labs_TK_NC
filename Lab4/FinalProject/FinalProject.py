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
    sConnection.write(sendStr.encode())
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
    prompt = "Please make a sentence about a person in the 3rd person style using these words: " + str
    return openai.Completion.create(model="gpt-3.5-turbo", prompt=prompt, temperature=0, max_tokens=10)

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