### installing gcc-7
```
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 100
sudo update-alternatives --config gcc
```


### add configuration file
```
modes = {                                                                             
    'debug': {                                                                        
        'sanitize': '-fsanitize=address -fsanitize=leak -fsanitize=undefined -fuse-ld=gold',                                                                                
        'sanitize_libs': '-lasan -lubsan',                                            
```
