echo "Compiling DESTRIPE..."
/usr/bin/h4cc OCM2_destriping.c read_data.c destripe.c write_data.c median.c avg_window.c mean.c mask.c -lm -o DESTRIPE -Wall -O3
echo "Compilation Complete..."
rm *.o
echo "Object files removed"
