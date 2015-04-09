# coding:utf-8

import PyPDF2
import os
import re
import sys
import logging


def natural_sort_key(s):
    return [int(text) if text.isdigit() else text.lower()
            for text in re.split('([0-9]+)', s)]


def showInstruction():
    print("using: pdfbinder.py targetFile sourceFile1 [sourceFile2 [sourceFile3 ...")
    print("must be targetFile and at least one source file")
    print("use quotes (\") if name contains spaces")


def checkList():

    targetFile = ''
    sourceFileList = []

    fSuccess = True

    if len(sys.argv) < 2:
        showInstruction()
        return

    for index, key in enumerate(sys.argv[1:], 0):
        if index == 0:
            targetFile = key.encode("utf8")
        else:
            sourceFileList.append(key.encode("utf8"))

    targetFileDir = os.path.split(targetFile)[0]
    execFileName = "pdfbinder"
    logPath = os.path.join(targetFileDir, execFileName.split('.')[0] + ".log")

    logging.basicConfig(filemode='w',
                        format='%(asctime)s %(levelname)s %(message)s',
                        datefmt='%m-%d %H:%M',
                        filename=logPath,
                        level=logging.INFO)
    console = logging.StreamHandler()
    console.setLevel(logging.INFO)
    logging.getLogger('').addHandler(console)

    output = PyPDF2.PdfFileWriter()
    for file in sourceFileList:
        print sourceFileList
        try:
            f = open(os.path.join("data", file), 'rb')
            inputPDF = PyPDF2.PdfFileReader(f)
            output.addPage(inputPDF.getPage(0))
        except Exception:
            fSuccess = False
            logging.error(sys.exc_info()[1])

    try:
        print targetFile
        outputStream = open(targetFile, "wb", buffering=0)
        output.write(outputStream)
        outputStream.close()
    except Exception:
        fSuccess = False
        print(sys.exc_info()[1])
    if fSuccess:
        logging.info('Файл {0} был успешно создан'.format(targetFile))
        logList = list(logging.getLogger('').handlers)
        for log in logList:
            log.flush()
            log.close()
        os.remove(logPath)  # удалим лог если все хорошо
    else:
        logging.warning('Во время исполнения были обнаружены ошибки! ' \
                        'Проверьте файл {0} на валидность'.format(targetFile))


if __name__ == '__main__':
    checkList()
    pass

