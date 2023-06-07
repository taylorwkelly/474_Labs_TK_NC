import serial
import openai

key = "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"
sConnection = ""
def waitForArduino():
    while sConnection.readLine() != "Requesting Pair":
        print ("Waiting")
    sConnection.write(b"Paired")

def sendToArduino(sendStr):
    sConnection.write(sendStr.encode())

def receiveFromArduino():
    str = ""
    nextLine = sConnection.readLine()
    while nextLine != "Done":
        str += nextLine
        nextLine = sConnection.readLine()
    if str == "Done":
        raise ValueError("Prompt invalid")
    return str

def promptGPT(str):
    openai.api_key = key
    return openai.Complete.create(model="gpt-3.5-turbo", prompt=str, temperature=0, max_tokens=10)

def program():
    sConnection = serial.Serial()
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