import serial
import openai

# descriptors for the openAI api key and the serial connection
key = "insert key here"
sConnection = serial.Serial()

"""
    Function: waitForArduino()
    Paramaters: None
    Outputs: None
    Purpose: Waits for the arduino to initiate a pairing process,
    once it is paired it will communicate that to the arduino
"""
def waitForArduino():
    # loop forever
    while True:
        # print to the terminal that we are waiting
        print('waiting')
        # read the line
        str = sConnection.readline()
        # decode and remove white space
        str = str.decode().strip()
        # if the string is the requesting pair string break the loop
        if str == "Requesting Pair":
            break
    # Writeback that we have successfully paired
    sConnection.write(b'Paired\n')

"""
    Function: sendToArduino(sendStr)
    Parameters: sendStr - String to send
    Outputs: None
    Purpose: Send the data back to the arduino
"""
def sendToArduino(sendStr):
    # remove quotation marks if needed
    sendStr.replace('"', "")
    # Write to the arduino the string to be sent
    sConnection.write((sendStr+'\n').encode())
    # write to the arduino that we are done
    sConnection.write(b'Done\n')
    # print to the terminal that we have sent 
    # the data to the terminal
    print('sent')

"""
    Function: receiveFromArduino()
    Parameters: None
    Outputs: str - string of tokens received from arduino
    Purpose: Get the data from the arduino
"""
def receiveFromArduino():
    # print that we are receiving data
    print('receiving')
    # initiate an empty string
    str = ""
    # loop forever
    while True:
        # read a line from the serial connection
        nextline = sConnection.readline()
        # decode and strip the whitespace from the line
        nextline = nextline.decode().strip()
        # if the string is the done command, break
        if nextline == "Done":
            break
        # else concatenate the information then move one
        str += nextline
    # if the string is empty something has gone wrong
    if str == "":
        # Raise error that we didnt receive anything
        raise ValueError("Empty string received instead of tokens")
    # return the string
    return str

"""
    Function: promptGPT(str)
    Parameters: str - string of tokens to be inserted into the prompt template
    Output: Result of the prompt
    Purpose: Prompt chatGPT with the tokens from the aruino to make a string about
    a person
"""
def promptGPT(str):
    # Assign the key
    openai.api_key = key
    # append the tokens to the prompt template
    promptstr = "Please make a sentence to someone you are talking to using these words: " + str
    # construct the prompt
    prompt = [{"role": "user", "content": promptstr}]
    # send the prompt to chatGPT and receive the response
    response = openai.ChatCompletion.create(model="gpt-3.5-turbo", messages=prompt)
    # get the content of the response
    result = response['choices'][0]['message']['content']
    # return the result
    return result

"""
    Function: program()
    Parameters: None
    Outputs: None
    Purpose: Facilitates the process of opening the serial port,
    waiting for the arduino, receiving from the arduino, prompting chatGPT,
    sending the data to the arduino, then closing the port
"""
def program():
    # set the port to COM5
    sConnection.port = 'COM5'
    # set the baudrate to 19200
    sConnection.baudrate = 19200
    # open the port
    sConnection.open()
    # wait for arduino pair
    waitForArduino()
    # get data from arduino
    prompt = receiveFromArduino()
    # send prompt to gpt and get response
    response = promptGPT(prompt)
    # send the data back to the arduino
    sendToArduino(response)
    # clsoe the port
    sConnection.close()


# Program entry point
if __name__ == '__main__':
    program()