# Note

## Error 
![map_error](../pic/note/Fig_01_error_change.png)

better
```
Error
Invalid file format:
Map must be fileending *.cub
Map Struckture: 
---
NO  <path texture>
SO  <path texture>
WE  <path texture>
EA  <path texture>

F <RGB>
C <RGB>

Your Map 
```


## Check 
```bash
./cub3D maps/bad/textures/textures_dir.cub  
```        
Error: get a --> `core dumped`
```
MLX42: LodePNG: failed to open file for reading
zsh: segmentation fault (core dumped)  ./cub3D maps/bad/textures/textures_dir.cub
```

## Check 
Argruments to start 
