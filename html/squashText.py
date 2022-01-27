#!/usr/bin/python3
import os

input = f"{os.getcwd()}/setup.html"
output = f"{os.getcwd()}/squash1.txt"
with open(input, "r") as file:
    text = file.readlines()
numLines = len(text)
#squashText = text.replace("\n","").replace(" ","")
newDoc = ""
firstLine = True
lineNum = 0
for line in text:
    line = line.strip().replace('\"','\'')
    if firstLine:
        newDoc += f"#define main_page_html  \"{line}\" \\\n"
        firstLine = False
    elif line != "":
        if lineNum == numLines -1:
            newDoc += f"\"{line}\" \n"
            # print('here')
        else:
            newDoc += f"\"{line}\" \\\n"
            # print(lineNum)
    lineNum += 1
#print(squashText)
with open(output, "w") as file:
    file.write(newDoc)
print("finish")

