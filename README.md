# yet-another-datamoshing-script
## Build and run
```bash
cmake .
```
```bash
make
```
### To run
> Example
```bash
./datamosh ddd.mov 7000 4300000 6500000 4
```
1º File route. It need to be .mov. Use ffmpeg if needed. Works best with no audio. </br>
2º How often to corrupt. </br>
3º Start chunk. Just eyeball it. </br>
4º End chunk. Leave it to 0 if you want to corrupt until the end. </br>
5º Offset of corruption. </br>
