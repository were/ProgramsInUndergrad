Replication and some simple enhancement of Hachisuka Toshiya's work published in 2008. A self-adaptive algorithm for image rendering.

[Progressive Photon Mapping] (http://www.ci.i.u-tokyo.ac.jp/~hachisuka/ppm.pdf)

Usage:
* For all the folder named `ppm-*`, enter the folder and use command `make` to get executable file `main`. Type command `./main` to see the results.

* When `*` stands for `china`, `bunny-*`, and `church`, please copy `bunny.fine.obj` to folder `models`.

* `small-ppm.cpp` is written by the paper publisher, is a demotration which is used for comparation with the simplest raytracing.

* Due to the configuration differences, it is hard to compare Hachisuka's demo directly, so I modified the file to get `compare.cpp`, which renders the same picture as `ppm-mine`. This is used for compare the speed of converging.

* Folder `raytrace` is used to compare the performance between raytracing and ppm, but there is something wrong with my configuration. I lost the correct configuration, and I never got the proper parameter again.

