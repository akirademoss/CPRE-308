#! /bin/bash
# pipe this script into the stdin of the print server
# ./test.sh | ./printserver -o log_file.log --n1 2 --n2 4


echo "NEW"
echo "NAME output1.pdf"
echo "FILE patreon.ps"
echo "DESCRIPTION patreon bw"
echo "PRINTER black_white"
echo "PRINT"
sleep 2
echo "NEW"
echo "NAME output2.pdf"
echo "FILE samplec.ps"
echo "DESCRIPTION test file"
echo "PRINTER color"
echo "PRINT"
sleep 2
echo "NEW"
echo "NAME output3.pdf"
echo "FILE musicpersonality.ps"
echo "DESCRIPTION music"
echo "PRINTER black_white"
echo "PRINT"
sleep 2
echo "NEW"
echo "NAME output4.pdf"
echo "FILE patreon.ps"
echo "DESCRIPTION patreon co"
echo "PRINTER color"
echo "PRINT"
sleep 2
echo "NEW"
echo "NAME output5.pdf"
echo "FILE musicpersonality.ps"
echo "DESCRIPTION music"
echo "PRINTER color"
echo "PRINT"
sleep 2
echo "NEW"
echo "NAME output6.pdf"
echo "FILE samplec.ps"
echo "DESCRIPTION test file"
echo "PRINTER black_white"
echo "PRINT"
sleep 2
echo "EXIT"
