# Setup EGL Software Rendering with Conda

Build and spin up the Docker container:
```
./run_docker.sh
```

Inside the Docker container:
```bash
./build.sh && ./test.sh
```

The test fails with the error:
> EGL\_DEFAULT\_DISPLAY initialization failed
> 0 EGL device(s) found
> FAIL!

But it passes after running `apt install libegl-mesa0` inside the Docker container (after running `apt update` first).
