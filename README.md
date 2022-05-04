# Destriping Ocean Colour Monitor 2 Data onboard OceanSat-2 satellite launched by ISRO in 2009.

## How to compile this project?

* Put all the scripts in a folder and run [compile.sh](https://github.com/rakeshkstp/DestripingOCM2/blob/main/compile.sh).

*Note that the C scripts used in this project are compiled using [h4cc compiler](http://manpages.ubuntu.com/manpages/jammy/man1/h4cc.1.html) to add support for OCM-2 
HDF-4 image files.*

* The compilation will create an executable file "DESTRIPE".
```
If DESTRIPE is not executable, then run $ chmod +x DESTRIPE
```

* DESTRIPE takes OCM-2 L1B file as input and updates it with the destriped image file.

The details of the algorithm is presented in
[Rakesh Kumar Singh and Palanisamy Shanmugam, 2018. A novel method for destriping of OCM-2 data and radiometric performance analysis for improved ocean color data products. Advances in Space Research 61, 2801–2819.](https://doi.org/10.1016/j.asr.2018.03.021)

## Author
**Rakesh Kumar Singh**
