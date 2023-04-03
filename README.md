OpenCV
* CV resources: Trucco, Forsyth, Hartley, Faugeras
* 3D inputs to 2D representation =>  lighting, weather, reflections, movements, lens imperfections, mechanical setup, finite integration time, electrical noies, compression artifacts => solutions: contextual knowledge, where we expect objects to occur, what size is implicit, machine learning techniques, statistical methods to reduce noise, time-lapse based methods like background subtraction
* downsampling an image
* sample space / image pyramid
* Nyquist-Shannon Sampling Theorem
* pyrDown => Gaussian blurring, down sampling
* traits in C++, variable introspection, 
* matrix inversion via: Cholesky, LU, and SVD decomposition
* saturation casting
* MatExpr
* SparseMat
* Integral images and their uses: https://docs.opencv.org/3.4/d7/d1b/group__imgproc__misc.html
* https://www.mathworks.com/help/images/ref/integralimage.html
* Haar wavelet transform
* https://www.mathworks.com/help/images/ref/integralimage.html
* https://www.mathworks.com/help/images/integral-image.html
[1] Viola, P., and M. J. Jones. "Rapid Object Detection using a Boosted Cascade of Simple Features". Proceedings of the 2001 IEEE Computer Society Conference on Computer Vision and Pattern Recognition. 2001. Vol. 1, pp. 511–518.

[2] Lienhart, R., and J. Maydt. "An Extended Set of Haar-like Features for Rapid Object Detection". Proceedings of the 2002 IEEE International Conference on Image Processing. Sept. 2002. Vol. 1, pp. 900–903.

https://levelup.gitconnected.com/the-integral-image-4df3df5dce35

* Covariance matrix (calcCovarMatrix)
* scrambled covariance
* PCA for very large vectors: eigenfaces technique for face recognition
* https://learnopencv.com/eigenface-using-opencv-c-python/
* invert using Guassian elimination / LU decomposition, singular value decomposition, or cholesky decomposition

## Functors

* function objects / functors
* Principal Component Analysis (cv::PCA)
* Analyzing a distribution in many dimensions, and extracting from that distribution the particular
subset of dimensions that carry the most information.
* Ability to generate a new basis whose axes can be ordered by their importance
* eigenvectors of the covariance matrix
* PCA object can compute and retain basis
* In modern CV, machine learning is intrinsic to an evergrowing list of algorithms.
* PCA and SVD considered building blocks
* Karhunen-Loeve Transform (KLT)
* RNG => multiple streams of pseudorandom numbers, one instance of cv::RNG for each thread in execution
* Multiply with carry (MWC) 
* Ziggurat algorithm
* singularity threshold

# Filters and Convolution

* image processing: using higher-level operators that are defined on image structures in order to accomplish tasks whose meaning is naturally defined in the context of graphical, visual images.
* filter: any algorithm that starts with some image, and computes a new image by computing for each pixel location some function of the pixels in I that are in some small area around that same x,y location. filter/kernel defines that area's shape and how elements of the small area are combined
* linear kernels: weighted sum of points around x,y in I
* median = nonlinear
* filter generally equals kernel; mathematicians tend to like kernel
* kernel support: size of array 
* linear kernel => convolution; sometimes used to refer any filter, even nonlinear
* anchor point: how kernel is aligned to input image

* OpenCV framework: python opencv/platforms/ios/build_framework.py ios --iphonesimulator_archs x86_64  --iphoneos_archs arm64 > out.txt 2>&1
https://docs.opencv.org/4.x/d5/da3/tutorial_ios_install.html
https://medium.com/@yiweini/opencv-with-swiaft-step-by-step-c3cc1d1ee5f1