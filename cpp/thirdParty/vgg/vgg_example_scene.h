#ifndef VGG_EXAMPLE_SCENE_H
#define VGG_EXAMPLE_SCENE_H

//---------------------
//- C++ simplified port of vgg_example_scene.m
//- Only define data from the first two view
//---------------------

// Extract fundamental matrix from projection matrix
mat vgg_F_from_P(const mat & P1, const mat & P2)
{
  mat X1 = P1.submat(1,0,2,3);
  mat X2 (2,4);
  X2.row(0) = P1.row(2);
  X2.row(1) = P1.row(0);
  mat X3 = P1.submat(0,0,1,3);
  mat Y1 = P2.submat(1,0,2,3);
  mat Y2 (2,4);
  Y2.row(0) = P2.row(2);
  Y2.row(1) = P2.row(0);
  mat Y3 = P2.submat(0,0,1,3);

  mat A00(4,4), A01(4,4), A02(4,4);
  A00.rows(0,1) = X1;  A00.rows(2,3) = Y1;
  A01.rows(0,1) = X2;  A01.rows(2,3) = Y1;
  A02.rows(0,1) = X3;  A02.rows(2,3) = Y1;

  mat A10(4,4),A11(4,4),A12(4,4);
  A10.rows(0,1) = X1;  A10.rows(2,3) = Y2;
  A11.rows(0,1) = X2;  A11.rows(2,3) = Y2;
  A12.rows(0,1) = X3;  A12.rows(2,3) = Y2;

  mat A20(4,4), A21(4,4), A22(4,4);
  A20.rows(0,1) = X1;
  A20.rows(2,3) = Y3;
  A21.rows(0,1) = X2;
  A21.rows(2,3) = Y3;
  A22.rows(0,1) = X3;
  A22.rows(2,3) = Y3;
  
  mat F(3,3);
  F(0,0) = det(A00); F(0,1) = det(A01); F(0,2) = det(A02);
  F(1,0) = det(A10); F(1,1) = det(A11); F(1,2) = det(A12);
  F(2,0) = det(A20); F(2,1) = det(A21); F(2,2) = det(A22);

  return F;
}

mat view1x ="110.002 107.028 194.261 122.236 107.573 188.542 193.958 423.613 382.67 387.2 391.86 121.999 196.619 364.768 118.964 131.536 372.441 120.248 125.654 277.537 397.986 245.231 370.491 132.796 276.303 405.312 270.711 370.497 136.306 415.649 400.908 421.925 441.243 256.02 260.812 134.026 392.674 407.649 202.3 263.756 371.34 137.104 139.831 143.319 364.599 403.948 226.156 397.977 411.326 391.917 201.746 253.881 371.562 377.713 400.92 428.503 148.39 160.248 230.005 248.773 407.403 378.072 417.086 233.771 151 154.646 243.97 423.507 483.232 366.504 146.168 210.483 401.608 411.094 158.024 204.655 391.168 372.275 417.373 163.739 267.614 366.519 406.974 155.792 160.954 253.361 231.902 412.82 418.176 163.057 401.343 409.143 440.542 148.493 211.967 169.939 370.967 436.671 271.57 404.332 151.855 156.73 212.238 265.382 268.458 148.933 221.068 401.002 175.977 449.168 161.918 456.362 176.494 221.965 330.868 173.702 181.337 390.016 149.028 323.829 386.236 481.83 438.95 176.68 179.511 185.507 181.606 148.238 155.604 322.712 379.529 181.849 188.915 191.729 323.353 329.808 195.378 334.855 158.992 391.993 397.704 331.946 157.461 198.597 227.883 340.75 367.993 335.631 408.763 234.681 330.35 361.208 149.423 152.626 157.687 271.971 212.125 202.46 330.502 334.948 208.6 202.038 236.937 330.259 351.903 215.284 310.094 371.672 341.324 208.987 219.848 236.208 268.147 270.954 348.585 149.222 244.441 309.104 329.258 341.149 237.209 268.251 205.979 209.729 155.572 241.206 244.945 273.753 151.843 200.358 216.712 219.679 373.835 376.892 388.764 337.494 355.629 213.079 288.582 200.227 371.205 380.93 221.702 247.91 337.02 141.869 301.908 221.985 313.954 385.369 213.2 231.708 329.867 246.752 252.145 266.925 309.453 340.129 343.756 359.49 363.735 11.0773 138.782 154.289 326.824 7.81425 160.902 205.998 231.488 210.081 228.606 374.015 377.106 250.546 305.127 322.215 348.852 381.254 260.303 230.515 236.329 250.295 200.386 244.956 291.554 196.949 282.005 284.934 161.403 293.278 179.994 240.611 97.118 132.153 206.964 235.597 230.27 302.761 188.217 428.874 210.409 314.012 415.703 333.768 166.92 174.236 219.586 231.216 307.463 327.873 245.004 162.119 176.889 180.377 204.882 266.93 222.956 243.176 368.857 225.682 206.365 266.833 30.9735 285.709 290.911 361.252 366.311 369.516 254.011 343.891 354.094 224.519 263.998 156.915 97.6188 207.373 67.2968 156.523 160.437 78.8722 85.993 290.173 25.15 30.0387 33.7638 207.265 199.653 230.285 416.408 426.578 79.1537 83.4473 293.601 297.888 380.03 68.5178 90.9239 366.996 29.9844 96.5152 180.034 225.495 223.181 291.907 307.515 96.5369 205.445 353.483 156.765 175.787 182.887 199.76 251.928 255.013 367.511 90.6769 154.007 297.791 161.164 69.4599 220.334 132.313 299.264 380.304 82.6823 175.416 183.876 281.297 366.501 216.114 285.285 343.342 20.5167 206.345 380.164 256.795 291.207 296.923 416.471 229.415 162.274 282.172 419.866 82.8583 210.603 343.763 416.439 426.305 366.484 162.434 219.677 260.433 329.428 244.322 257.052 322.332 333.864 354.041 250.841 229.121 245.529 267.727 70.4159 212.891 220.625 286.701 310.527 14.4638 206.395 368.729 161.428 249.061 263.111 80.4203 86.7307 220.892 266.636 299.023 306.204 287.521 68.4613 97.5578 232.034 378.983 206.497 220.311 229.144 247.391 86.4941 414.013 79.0219 162.233 305.867 309.147 75.5956 83.681 14.4871 90.021 162.456 426.624 97.5257 68.9561 75.8155 162.494 220.008 231.329 228.186 268.558 236.96 140.832 426.828 245.38 72.8873 85.5731 88.6607 94.975 142.772 162.443 217.402 233.614 143.615 70.4727 234.766 258.088 262.205 376.733 233.203 236.163 217.924 250.106 68.7059 99.2483 253.908 375.993 206.443 213.827 297.962 217.231 242.083 252.538 266.887 291.854 376.282 225.047 235.254 270.945 274.997 111.101 139.2 230.871 240.794 297.223 380.163 163.483 240.835 299.029 233.584 240.959 301.465 258.247 284.452 315.717 256.589 284.103 286.699 236.299 318.06 218.937 230.496 209.607 144.488 163.487 261.586 269.126 273.286 280.964 471.838 253.203 287.879 447.528 288.953 327.706 470.895 251.603 328.703 257.058 448.449 468.286 205.759 275.074 426.246 195.791 256.643 145.548 469.927 249.038 252.977 456.982 163.473 194.781 200.338 336.116 468.945 164.35 11.732 331.522 452.857 247.86 252.677 291.941 460.082 337.836 284.984 296.501 451.735 448.453 463.9 253.267 284.409 345.065 244.828 292.84 447.41 454.392 164.441 13.6246 259.002 263.031 280.042 204.932 447.484 452.24 348.204 164.413 287.669 307.926 13.5256 242.538 249.339 295.997 447.414 149.268 253.895 287.432 467.83 262.066 336.281 249.834 254.541 288.109 236.749 297.585 13.6926 262.132 358.915 248.84 253.617 370.082 290.589 47.3555 50.1368 363.218 374.422 237.931 245.083 302.066 254.342 375.634 164.3 291.335 369.83 372.833 455.332 166.901 246.443 251.355 108.53 236.996 372.052 304.757 250.706 159.736 260.709 310.43 294.376 299.446 303.291 20.0422 46.9254 237.484 246.585 311.384 467.262 29.9283 33.914 42.793 51.3573 150.117 299.484 304.62 86.409 98.9908 114.289 142.05 146.326 377.322 183.51 236.494 149.658 299.484 306.697 293.554 145.286 170.029 467.351 199.708 312.25 211.575 228.786 306.575 136.394 178.584 385.986 245.523 139.38 307.087 98.1094 294.512 355.627 234.469 245.316 163.212 171.227 175.643 307.715 182.584 294.74 299.273 252.937 257.086 282.908 290.815 287.13 196.05 243.251 248.086 391.551 111.246 296.581 104.184 307.523 389 297.069 230.051 241.991 247.01 255.059 269.715 305.689 96.6939 238.591 394.849 399.644 40.705 404.321 215.852 237.546 23.8576 20.5339 105.372 206.238 202.064 399.93 404.951 421.796 410.151 246.193 45.4503 76.2883 39.9267 82.7786 34.7957 160.307 80.1721 50.3769 70.9584 76.3559 234.564 244.366 74.6831 462.494 26.6708 64.0301 69.7976 242.418 49.6848 46.2878 59.9966 82.1234 414.873 42.7625 88.9783 50.5018 84.8174 241.28 17.598 56.1484 45.6711 416.734 425.234 22.4754 86.7696 91.8828 252.26;\
9.10115 9.90367 11.1293 14.4689 16.4958 15.9615 15.3451 16.1701 19.1966 19.3138 18.902 19.5322 19.7082 20.1985 23.1945 22.2015 23.8916 25.7371 26.1476 27.2517 27.1731 28.2438 28.027 30.2007 30.2013 30.8541 32.2134 32.0591 34.5128 34.5659 34.4234 34.7776 34.9725 37.036 37.5253 39.1859 38.8106 38.9463 40.0493 41.1374 41.2759 42.1104 41.9465 41.8821 42.9766 42.3249 45.0414 44.5624 45.5171 46.1999 46.9441 47.7269 46.2987 46.9193 46.6554 46.8387 47.9065 47.6755 48.6241 49.3122 49.0009 50.828 51.5439 52.0615 53.2008 52.785 53.2104 53.632 52.8884 53.7935 54.4219 54.9703 55.2889 55.9781 56.8795 56.9255 56.8709 57.7717 58.0047 58.0556 59.1723 58.8211 60.148 61.2899 61.3041 61.1242 61.2974 61.9368 62.5338 64.0684 65.357 65.4292 65.3359 66.7289 67.0814 68.1013 67.8029 67.8461 70.8301 70.8851 72.0744 72.317 72.2666 71.9773 72.1999 72.9643 73.9595 74.1441 74.752 75.2849 76.0875 75.7182 78.4514 79.3243 78.8586 81.3076 81.9129 81.7708 83.5649 84.1382 84.7707 84.6939 86.4323 88.1289 88.4654 88.9997 91.2694 91.7459 92.1496 91.8706 92.2725 94.1647 94.0508 93.7546 95.7523 96.1647 98.6283 98.0447 98.9536 98.4685 99.1061 101.402 101.952 102.408 102.034 102.06 102.228 103.238 104.402 104.584 105.274 105.8 106.105 106.977 108.09 107.549 109.642 110.696 111.851 112.509 114.343 115.45 114.061 114.542 114.891 115.858 116.055 116.1 116.817 117.672 118.073 117.771 118.289 118.35 118.43 119.977 119.812 119.902 120.294 120.361 120.511 120.473 122.699 122.528 123.373 124.058 124.256 124.035 124.932 125.443 125.278 125.699 126.469 125.69 125.748 127.231 126.958 127.629 127.775 128.534 129.083 129.567 130.696 130.735 131.302 133.058 132.978 133.427 133.59 134.188 134.912 134.761 135.048 136.013 135.72 135.705 135.908 136.267 136.415 136.897 136.594 138.052 138.055 138.193 137.806 138.509 140.333 139.734 139.614 141.464 140.616 140.927 141.996 143.594 142.856 142.589 142.781 143.1 146.137 146.68 146.727 147.034 149.358 151.213 151.149 152.564 151.616 151.973 155.142 154.808 156.4 156.54 158.263 157.766 157.601 158.404 158.656 159.006 160.011 160.353 161.523 161.572 161.407 161.541 162.959 162.799 163.323 163.469 162.875 163.004 164.215 165.633 165.343 164.751 164.727 167.714 167.599 167.787 167.811 168.878 170.105 169.546 172.089 172.758 172.92 174.967 174.634 174.51 175.311 175.165 175.084 175.612 175.609 177.011 178.408 177.97 178.858 180.137 180.134 181.356 181.433 181.2 181.643 181.981 181.82 182.024 182.45 182.992 183.051 183.937 185.019 185.149 185.377 184.968 186.293 187.189 186.883 186.182 187.719 188.177 188.711 189.07 189.665 190.059 190.171 191.809 191.864 191.88 193.185 193.209 192.993 192.665 193.112 193.055 193.848 193.877 194.035 194.123 195.307 195.821 195.899 197.75 197.091 196.68 197.177 197.626 197.506 197.613 197.901 199.076 199.04 199.024 200.136 199.663 199.965 201.093 202.366 202.343 203.111 204.001 204.82 205.007 204.851 206.13 206.992 207.165 207.211 206.047 208.476 208.634 209.131 208.876 208.844 209.858 210.002 210.133 210.827 211.278 213.776 215.38 214.866 214.385 216.101 215.868 215.923 216.215 216.442 216.895 217.028 217.37 218.031 218.322 217.56 220.746 221.317 220.598 220.789 221.407 220.778 221.649 224.169 223.995 224.202 224.404 225.136 225.066 225.104 224.793 226.442 226.013 227.225 227.07 226.874 227.483 229.809 230.193 230.872 232.08 232.003 231.413 232.946 233.63 233.358 235.395 234.898 234.909 235.895 235.567 236.853 238.948 239.383 242.917 243.077 243.253 243.41 243.206 243.208 242.67 242.966 244.205 246.107 247.79 248.161 249.031 248.67 248.805 251.349 251.544 252.2 252.028 252.606 252.68 254.179 254.025 255.912 255.924 256.31 256.938 256.634 257.327 257.564 257.838 259.622 259.966 261.809 261.984 262.622 263.07 263.028 262.944 263.167 264.669 265.648 267.923 268.186 268.714 270.431 271.984 274.022 275.011 274.944 274.844 280.059 280.257 280.22 280.256 284.225 285.562 286.148 287.408 288.111 289.026 289.215 289.22 289.383 289.717 291.631 293.669 294.016 295.671 297.087 297.112 298.085 300.272 300.381 302.882 303.102 303.682 306.392 305.574 305.533 306.909 307.692 308.794 309.85 311.24 311.067 311.553 313.068 314.016 314.067 315.32 315.519 316.995 317.66 317.956 318.483 319.415 319.472 319.402 318.931 320.302 321.598 322.042 322.329 324.22 330.711 333.974 334.028 335.019 336.003 336.25 338.058 338.472 338.263 339.91 340.473 340.442 340.481 340.561 341.008 341.067 341.935 343.262 342.56 345.101 346.091 345.911 346.349 346.193 348.044 348.852 349.215 348.78 350.315 351.547 352.467 354.129 353.431 353.863 354.084 356.278 357.657 358.922 360.389 361.215 363.186 363.408 364.78 369.491 370.427 370.502 370.889 371.745 371.701 372.812 375.011 375.176 376.529 376.651 377.459 377.94 381.837 383.478 384.808 384.81 387.014 387.915 388.842 390.253 392.134 392.829 393.474 392.79 393.968 394.909 394.516 396.807 398.708 397.986 398.546 397.754 397.699 399.826 399.359 399.407 400.701 400.554 401.17 401.169 401.432 402.118 401.617 401.803 401.866 402.74 403.83 404.009 405.273 405.866 405.94 407.237 408.264 408.135 408.221 409.498 408.794 410.598 410.109 410.909 411.906 412.122 412.857 414.526 416.301 417.733 418.458 417.892 419.027 420.039 419.958 421.151 420.728 421.355 422.738 423.785 424.785 425.349 425.598 425.616 425.532 425.732 426.637 428.194 428.244 427.868 427.724 430.371 430.051 431.449 430.889 432.079 433.129 433.944 436.939 436.896 438.452 438.342 438.13 439.881 445.875 446.185 446.819 451.897 455.762 457.9 458.004 458.921 459.698 459.458 461.242 462.5 463.395 464.029 465.008 465.605 471.406 473.013 474.494 476.123 476.444 477.355 477.186 481.711 482.748 483.029 483.279 486.846 487.255 489.028 489.244 489.928 490.196 489.806 491.228 492.097 493.023 494.281 494.251 494.261 494.472 495.197 497.812 498.041 498.473 499.883 499.533 501.025 500.83 502.377 503.385 502.625 502.76 502.569";
mat view1P = "-510.068621 -12.940054 -259.37648 -130.4363; -7.67014704 -517.021656 -257.29121 -66.502356; -0.0324901697 -0.0517872258 -1.01075745 -0.484721083";

mat view2x= "396.344 126.122 254.018 288.976 285.704 130.004 279.438 282.869 432.803 138.449 291.882 396.393 127.393 266.02 278.437 281.703 284.91 271.684 422.298 133.9 131.103 397.261 449.068 460.839 138.891 274.712 444.692 397.353 421.284 426.321 433.84 149.502 267.293 402.676 441.352 466.115 133.369 144.901 211.412 205.656 263.839 137.168 452.366 237.089 257.744 267.819 447.87 462.967 241.09 434.755 152.704 397.463 461.108 252.236 453.548 466.567 160.078 430.832 156.138 215.337 268.099 271.967 208.926 438.234 149.38 163.823 447.3 154.551 160.04 245.648 278.579 487.976 238.75 434.813 268.616 163.133 401.777 145.788 396.437 440.123 166.435 170.358 425.867 437.122 149.575 163.614 146.087 432.265 154.867 172.92 175.418 169.95 218.906 275.939 279.188 227.692 232.354 159.086 171.538 420.867 486.939 178.298 347.887 171.508 175.526 228.623 474.988 146.063 415.209 410.213 186.301 413.965 182.751 145.038 153.433 407.253 189.122 428.031 401.754 157.486 184.141 189.317 193.194 195.841 337.075 421.938 157.453 338.623 343.405 347.458 351.684 155.73 195.298 391.698 442.674 352.039 358.069 146.383 203.422 152.952 200.356 210.995 339.519 242.391 347.986 283.596 339.522 345.437 382.032 208.066 350.86 353.816 339.496 345.479 157.517 151.511 370.313 394.084 207.839 215.04 145.333 152.776 222.247 322.726 367.191 215.089 357.343 227.677 244.453 247.686 277.846 280.917 153.645 252.687 343.487 357.152 148.964 228.116 245.367 277.915 280.99 321.87 208.779 211.934 215.867 362.092 400.459 286.551 397.229 205.709 223.58 353.398 374.488 153.59 208.778 219.682 356.058 405.172 205.612 138.207 299.684 353.041 228.923 253.333 328.832 256.13 410.933 375.782 134.592 229.762 312.806 325.756 219.308 239.386 379.102 342.832 359.922 383.714 255.112 260.679 354.096 160.043 223.713 310.566 372.635 397.394 211.93 385.988 401.017 208.268 216.187 236.062 239.578 326.007 347.631 405.346 260.947 365.907 316.075 335.106 269.203 450.867 238.223 244.281 258.965 205.876 202.071 253.351 301.455 294.819 128.517 160.983 88.4904 164.306 183.538 303.062 202.086 238.355 243.62 471.038 188.42 193.452 207.218 313.083 451.767 216.672 325.204 170.632 177.902 199.187 347.98 163.761 184.453 204.34 226.756 317.935 341.713 180.86 210.805 253.39 332.602 230.129 251.632 275.997 161.224 233.07 15.3756 212.323 295.778 300.597 381.44 262.86 386.678 391.361 19.9724 181.233 227.305 230.028 273.093 296.275 359.881 372.818 156.51 237.288 55.4932 89.1372 212.5 301.092 62.549 68.6539 155.663 388.335 8.9832 18.5382 205.079 212.483 299.934 295.486 389.589 74.2868 230.399 452.187 308.181 81.2046 404.235 468.736 14.4873 57.1794 87.681 386.497 389.611 67.165 162.935 181.232 184.062 232.922 223.571 230.287 263.339 301.91 317.872 57.43 87.649 211.15 371.227 78.4139 155.909 179.304 81.064 152.397 163.604 192.501 160.41 307.935 57.3649 227.549 233.531 370.519 72.5083 127.316 179.021 188.121 290.939 211.454 222.805 404.323 160.282 294.934 386.373 127.545 234.69 358.829 300.982 307.034 404.096 261.982 288.858 236.979 225.164 258.539 467.559 72.6746 216.893 451.475 359.703 457.692 464.799 75.8883 252.242 261.271 269.19 388.479 265.84 321.762 342.977 335.527 467.844 347.841 259.035 372.254 236.739 250.362 253.723 276.62 341.834 214.875 219.241 222.103 227.634 74.8033 211.646 320.797 403.677 57.4822 271.865 160.502 165.122 276.974 315.859 385.403 390.089 297.111 309.118 316.635 320.91 68.5001 72.0551 77.1469 163.919 212.464 227.315 239.14 255.425 88.8551 56.6093 316.037 77.635 319.559 402.842 68.4374 163.905 403.096 64.5443 73.2215 448.746 80.6257 67.5787 76.6336 88.7067 161.073 227.001 238.35 277.516 57.0998 447.838 467.853 137.616 161.415 241.609 60.9645 72.6133 78.8657 86.0234 242.346 270.835 62.7456 266.594 58.4878 140.468 240.462 224.394 243.947 258.165 397.338 56.7593 220.194 307.961 90.8367 211.492 223.814 260.808 275.58 301.345 231.937 399.683 242.81 279.736 238.008 138.77 249.892 103.66 135.056 309.534 240.882 248.394 403.072 311.839 246.417 266.838 294.133 326.798 243.657 264.938 267.558 293.562 296.92 268.632 225.189 329.45 237.751 215.278 162.463 270.945 278.282 282.41 289.697 140.951 214.979 261.495 297.969 141.606 212.419 162.483 293.545 340.091 299.58 259.669 264.082 341.305 265.479 200.716 211.108 284.5 142.876 200.799 264.915 208.226 252.451 205.27 142.681 256.887 261.22 496.383 162.381 142.556 199.283 204.956 272.99 349.895 255.448 497.178 303.057 466.643 262.827 351.913 295.64 272.775 502.563 499.567 272.066 261.663 295.414 252.347 360.196 503.325 304.378 163.312 465.938 497.098 267.995 272.113 209.621 163.41 271.853 298.017 364.253 496.467 249.901 320.787 308.125 465.544 258.323 262.164 298.95 271.641 145.909 271.034 352.073 495.294 257.903 262.684 299.769 265.182 310.03 495.309 271.075 256.816 309.918 376.973 261.872 388.082 391.808 498.094 36.5254 244.748 252.637 382.458 315.402 389.572 163.343 308.043 262.468 397.905 394.818 387.772 391.094 166.353 265.078 269.966 294.947 163.241 254.402 259.585 159.916 165.021 243.576 19.4853 310.009 158.697 387.41 393.103 494.523 101.53 258.773 309.96 317.169 324.093 264.183 269.174 306.717 312.489 32.8193 244.333 14.581 18.6587 28.6047 151.781 37.5567 76.7756 147.049 312.505 319.521 87.5406 90.717 107.027 138.145 142.243 242.464 146.634 183.696 319.956 136.414 400.172 313.282 326.492 320.625 140.96 171.539 202.599 408.372 215.269 131.325 234.489 176.846 405.974 410.59 133.778 170.341 95.3521 314.457 87.7505 233.514 307.651 93.1709 159.928 258.453 376.835 177.249 181.409 258.402 189.572 314.238 196.603 204.443 303.731 193.115 250.627 255.677 300.219 323.497 418.31 93.161 104.324 300.728 415.88 117.375 235.197 311.863 248.921 254.362 279.95 259.092 263.837 83.9642 245.536 429.135 460.262 18.8581 229.147 254.275 218.841 92.2583 435.436 207.918 275.657;\
8.0595 9.19697 8.55713 11.4663 13.0778 14.0555 14.0547 13.8736 14.5201 17.0179 16.5513 17.7136 18.903 19.2385 20.3891 20.5723 19.8903 20.6598 20.1185 22.1438 22.7991 23.4168 23.3398 23.2779 23.734 24.5498 26.7853 27.8006 28.6181 28.4168 27.3092 30.2215 30.4947 29.9199 29.7257 29.8929 31.4873 31.0524 30.9259 31.766 32.2111 33.442 32.6095 34.0245 34.9616 35.4762 36.1363 36.4307 36.9446 37.0384 37.7811 39.0269 39.2684 39.5932 40.467 40.4812 40.833 40.7366 42.0927 42.3954 41.6993 42.7319 44.6935 45.4215 45.9352 45.4103 46.2799 47.2497 47.4797 47.1738 47.275 47.2514 48.3473 48.2376 49.0054 51.4921 51.3288 53.0501 53.1798 53.7083 54.6898 56.9212 57.2354 56.5695 58.9223 59.1875 59.9462 59.9791 60.7973 61.359 61.1747 62.8665 62.8399 62.7794 62.8397 64.3822 65.9238 67.0971 68.0083 68.1245 68.7378 69.2951 70.1018 71.0055 70.784 70.44 70.6901 71.6409 72.3819 73.1693 76.5508 77.3836 79.3571 80.7985 81.4878 80.6305 81.4859 82.6431 85.5161 86.3434 85.2585 86.0676 87.3195 86.8943 86.711 88.3706 89.8588 90.9229 90.9941 91.0363 91.5708 92.6947 92.9862 93.8254 94.2233 96.3918 96.07 96.82 96.7596 98.0993 98.0704 97.4511 99.8902 100.308 101.533 102.399 103.919 103.887 104.239 106.169 106.07 106.378 107.936 107.792 108.957 110.131 110.319 110.146 111.44 111.168 113.14 113.289 113.418 113.103 113.429 114.002 113.7 115.25 114.922 115.115 115.483 115.459 116.994 117.489 116.998 117.138 118.186 117.73 117.78 117.74 117.814 117.682 119.106 119.107 119.297 120.401 120.477 121.072 121.068 122.083 122.801 124.346 123.748 125.103 125.038 124.754 125.26 125.104 125.286 127.426 126.629 128.181 128.831 128.741 128.457 129.592 130.086 130.811 132.431 131.803 131.68 131.745 132.767 133.42 133.642 133.633 133.997 133.81 134.921 134.724 134.883 135.669 135.955 137.359 137.434 137.158 137.954 138.023 138.265 138.924 139.381 139.785 138.777 139.887 139.697 140.274 141.453 140.914 142.145 141.234 145.352 144.98 145.803 145.795 146.846 147.781 150.978 151.012 151.018 151.873 153.174 153.333 155.247 155.143 155.076 154.86 157.752 157.708 158.279 158.078 159.092 158.728 159.396 159.31 159.68 160.666 161.731 161.835 161.736 161.188 161.506 162.732 163.735 162.592 163.087 163.428 162.819 164.064 164.013 164.368 166.814 167.598 167.907 168.354 169.114 168.855 170.077 170.233 173.126 173.665 174.354 175.64 175.118 175.175 175.71 176.358 175.68 175.839 176.141 176.074 176.018 176.188 176.582 177.069 177.911 177.565 177.749 179.498 180.407 180.248 179.789 180.39 180.656 180.634 182.53 183.08 182.47 184.036 184.147 185.143 184.903 185.133 186.046 187.214 187.221 186.445 187.582 187.685 188.518 187.902 187.987 188.616 188.855 189.711 189.678 190.003 191.25 190.587 190.822 191.583 191.763 193.081 192.792 192.314 193.463 193.861 193.867 194.022 194.986 195.329 195.204 194.954 196.315 195.843 196.825 197.069 198.165 198.242 198.603 199.306 199.007 198.849 199.128 200.225 200.268 200.225 200.988 200.47 200.828 201.409 201.61 201.715 204.407 204.494 203.641 204.761 205.265 205.442 207.068 207.232 207.023 208.228 208.621 207.9 210.281 210.215 210.079 210.839 211.218 210.851 210.793 210.931 212.001 211.252 211.958 213.057 212.403 214.122 215.455 215.436 217.243 217.064 216.76 216.381 217.3 217.753 218.098 217.98 217.905 219.126 219.954 219.032 219.14 220.206 219.772 220.569 221.341 221.135 221.113 221.045 222.871 224.011 223.987 223.701 223.335 225.004 225.062 225.622 226.298 227.215 227.251 226.781 227.191 228.442 228.255 229.783 231.031 230.589 230.99 231.819 232.504 234.137 235 234.984 234.858 237.291 237.825 237.619 238.178 238.325 237.598 237.563 237.908 238.847 239.3 242.764 245.669 246.348 247.701 249.563 250.075 250.1 249.887 251.541 252.357 253.114 252.316 254.06 253.711 255.341 256.051 255.821 255.886 258.284 260.104 259.906 260.28 260.439 260.858 260.805 261.17 261.687 261.505 264.21 263.841 266.019 265.759 267.302 269.142 270.929 271.991 272.156 273.058 275.747 277.092 277.124 279.336 280.159 279.923 280.087 280.326 285.73 285.723 285.708 286.001 286.135 289.144 291.165 290.739 292.093 293.436 295.094 295.799 295.785 295.969 296.185 299.275 299.132 300.464 301.148 301.973 302.136 304.021 304.316 304.961 307.158 307.809 307.925 308.788 311.107 312.93 314.392 314.17 316.214 315.823 315.979 318.526 318.509 318.971 319.773 320.452 320.404 320.855 321.571 323.018 322.827 322.896 324.558 325.589 329.306 329.301 329.784 329.755 331.272 331.322 331.851 333.407 341.512 342.561 344.534 346.521 346.882 348.898 348.746 349.469 349.809 351.032 351.616 351.497 353.486 353.475 353.729 354.968 356.501 356.657 356.615 357.653 359.968 359.775 360.953 360.751 363.03 363.969 363.845 365.418 367.773 367.585 368.201 369.111 370.21 369.505 370.061 373.379 373.389 374.812 375.789 378.254 378.124 378.344 380.239 384.71 385.282 385.892 389.933 391.05 391.291 390.622 392.924 393.8 396.071 397.497 397.937 398.383 401.71 403.849 402.461 404.126 405.533 405.523 405.535 406.999 407.061 407.117 409.868 409.773 410.057 410.92 412.458 412.613 413.225 413.044 412.882 414.798 415.459 414.319 415.382 414.371 417.437 417.442 418.45 420.046 421.445 421.251 422.069 421.923 422.074 421.789 423.343 425.102 424.962 425.373 425.183 425.572 425.953 425.92 426.465 426.751 429.243 430.229 429.374 430.24 430.911 430.488 431.232 432.066 433.207 434.414 435.841 436.655 437.38 438.255 438.881 439.101 439.843 443.354 442.823 444.299 445.299 446.354 445.905 446.605 446.955 448.106 450.249 451.044 451.216 451.023 453.646 454.793 455.257 457.718 458.271 460.456 460.06 459.686 460.845 461.216 460.957 460.517 461.976 461.799 463.052 462.68 466.523 466.993 468.238 468.358 468.624 471.595 471.666 472.458 473.469 473.422 473.797 483.968 487.011 486.831 488.391 495.408 498.811 499.244 499.508 500.14 502.97 503.28";

mat view2P ="-736.733007 -13.520626 -388.49702 -828.164444; -12.1721289 -749.304825 -375.275988 -560.653317; -0.0290853877 -0.0622642584 -1.4689936 -3.21406664";


mat Xi ="105 107 114 128 129 143 144 150 167 183 184 189 190 191 198 200 204 207 212 214 215 227 228 235 239 243 245 246 248 249 251 253 256 257 261 264 266 267 270 273 275 277 280 284 293 294 295 297 300 305 314 316 319 320 324 327 329 330 336 337 338 340 341 345 347 348 354 364 372 374 375 376 377 385 389 395 400 401 402 403 413 418 422 425 436 441 443 444 445 447 448 450 451 452 456 457 460 461 464 465 466 468 469 470 476 477 479 480 482 483 484 485 486 487 489 490 493 494 495 498 499 502 505 506 509 510 513 516 517 520 528 530 532 533 538 539 541 542 558 560 564 569 570 572 576 577 584 585 589 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 103 104 115 138 175 178 179 180 181 185 199 205 209 221 223 231 237 240 258 262 290 298 326 357 358 366 378 0 381 382 414 416 421 435 440 481 491 496 512 540 553 567 575 582 586 595 596 598 601 615 616 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 59 60 66 67 75 81 84 85 87 94 97 126 130 134 147 153 165 173 174 176 182 193 197 206 210 220 232 269 274 287 288 303 307 317 328 346 349 355 360 373 380 390 391 393 404 406 415 426 433 438 442 454 462 473 514 545 594 599 609 618 621 623 624 626 627 636 638 642 647 652 22 23 24 25 27 29 34 35 36 37 40 41 43 44 49 50 51 53 57 61 72 73 74 88 89 90 96 100 101 102 106 108 116 118 125 131 132 133 136 140 146 148 158 159 162 168 170 171 194 196 202 203 208 211 219 229 230 236 241 242 244 250 259 260 263 265 271 276 281 283 289 310 312 318 321 322 323 342 344 350 352 363 365 368 383 387 394 398 399 410 411 420 428 430 449 455 458 478 488 500 504 511 548 551 555 562 563 568 578 588 591 592 604 605 614 630 633 643 648 656 658 662 663 664 665 666 667 672 673 674 675 676 677 678 680 683 684 686 690 691 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;\
95 96 106 114 115 132 139 144 164 184 185 177 190 191 196 199 206 211 214 219 220 222 227 239 241 246 249 247 250 252 255 253 259 258 266 271 269 275 277 278 279 282 286 289 299 303 306 305 310 314 323 328 327 329 340 344 347 348 349 350 354 355 356 359 362 363 364 382 391 389 393 396 398 409 411 428 422 435 434 432 436 446 454 451 463 469 464 467 465 470 472 473 475 478 476 477 481 482 484 486 487 491 492 488 493 494 497 499 501 503 505 506 502 509 510 511 513 514 515 519 520 525 529 530 532 533 536 541 542 546 550 552 555 556 561 562 563 566 578 580 584 591 592 594 597 600 605 606 610 120 162 235 237 333 339 351 367 408 417 419 433 437 447 504 518 526 531 534 549 554 582 604 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 93 94 103 131 165 182 175 176 179 173 201 202 212 218 209 232 238 243 264 267 301 311 343 373 374 385 400 0 403 404 438 444 449 462 459 500 521 516 535 564 576 588 599 607 608 622 623 626 634 645 646 81 90 92 97 160 186 197 290 302 317 358 376 388 390 418 420 430 539 572 596 625 648 44 45 51 54 59 71 68 69 73 78 79 117 125 124 134 138 157 171 172 161 180 189 193 200 207 215 226 276 273 293 294 313 315 324 345 361 369 375 378 395 401 421 416 415 439 431 443 452 460 458 468 485 483 496 545 567 617 631 642 650 649 655 656 663 660 669 671 674 681 685 3 1 2 4 8 6 14 18 13 19 26 22 20 25 23 29 40 28 38 27 60 50 47 55 53 76 82 80 85 89 87 84 105 100 113 116 121 123 130 126 137 136 150 154 159 158 166 168 187 192 198 203 210 213 217 233 231 240 244 245 248 256 262 260 265 268 280 284 288 287 292 326 320 330 335 336 338 370 366 365 372 386 383 397 414 412 426 423 424 445 440 456 453 457 471 479 480 495 508 543 527 553 571 595 575 586 583 590 602 613 616 614 637 640 644 641 667 676 683 689 692 695 699 693 697 698 701 705 708 707 709 710 713 711 714 716 718 721 722 724 41 46 49 62 70 75 77 119 128 149 170 174 181 208 296 308 316 341 353 368 425 450 466 512 523 528 544 615 629 647 662 677 678 679 680 688 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;\
55 58 63 66 67 73 84 88 106 116 117 104 124 132 136 134 148 153 158 162 163 151 169 178 180 182 189 186 191 188 193 187 199 198 200 206 203 211 212 208 210 215 216 221 227 224 223 226 232 238 258 255 254 260 269 272 275 270 274 277 282 281 284 286 290 293 292 312 313 315 318 326 328 338 344 370 359 373 375 364 374 395 394 387 415 423 407 409 410 417 418 419 436 438 426 428 431 432 437 441 439 450 452 440 446 449 456 455 459 461 463 464 460 468 471 470 474 475 476 481 482 485 489 491 492 494 495 499 500 501 506 510 514 513 516 517 519 521 530 532 534 536 538 541 543 544 553 554 559 71 92 175 176 261 265 279 298 337 352 355 368 378 392 462 478 487 490 502 505 511 533 548 53 62 69 76 85 126 135 144 155 171 183 190 192 195 196 202 237 243 248 271 317 329 339 343 349 350 354 361 365 369 380 386 389 397 398 400 402 412 421 427 429 445 525 526 549 54 57 61 79 100 121 112 108 118 101 143 141 152 154 140 172 173 179 201 207 229 239 268 306 307 322 341 581 331 332 377 385 396 414 404 458 488 477 493 522 529 537 545 558 560 574 575 577 592 588 591 46 49 51 59 102 122 137 222 230 252 300 305 314 316 353 362 366 496 524 542 570 595 7 8 15 23 26 38 30 32 39 40 31 72 75 74 77 80 97 110 111 96 119 114 129 130 139 150 157 214 209 231 225 236 250 256 283 289 303 311 304 324 330 371 348 345 390 363 384 383 411 403 422 447 433 466 508 518 563 597 589 603 599 602 604 615 606 614 619 620 625 639 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 12 17 28 36 44 29 68 78 86 109 115 120 147 233 246 251 273 278 299 360 388 420 473 484 486 498 568 578 598 605 624 629 626 621 648 43 45 50 83 87 98 103 105 113 125 128 133 146 156 164 181 184 185 204 205 217 218 228 234 235 240 249 257 262 280 285 320 323 333 335 347 351 379 401 413 430 434 509 512 515 571 573 576 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;\
42 44 51 48 49 55 74 84 107 114 115 91 123 140 139 138 150 156 158 160 161 142 159 173 182 178 192 184 191 187 190 181 201 200 207 208 205 215 217 212 214 223 225 234 247 233 232 231 237 244 267 266 265 269 284 283 291 289 294 296 298 300 301 307 306 308 310 325 327 326 331 341 348 346 354 387 369 390 391 373 383 423 422 398 452 463 427 428 430 433 434 431 469 474 438 443 450 451 458 462 459 490 492 464 473 477 483 480 484 487 489 491 486 499 497 496 500 501 502 505 506 507 512 513 515 516 519 524 525 527 533 535 541 539 549 551 552 555 567 570 574 581 587 589 591 593 602 604 606 52 81 166 172 273 277 295 309 350 364 363 378 400 416 488 504 510 514 540 532 536 571 599 37 50 53 61 77 131 135 137 151 168 183 193 188 194 195 204 242 254 257 282 329 356 352 366 357 375 362 379 386 388 404 410 399 406 426 414 417 444 436 439 453 468 559 560 596 39 43 47 60 96 124 111 108 116 89 148 141 149 145 122 167 164 179 210 216 241 245 280 318 320 338 365 631 344 340 384 409 420 446 421 481 521 503 517 556 569 585 594 609 610 622 623 626 643 635 638 14 29 28 45 106 112 134 235 250 260 313 316 333 328 361 380 376 523 557 590 618 641 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 2 34 72 78 99 104 110 109 126 121 127 144 153 162 180 186 176 209 211 224 229 248 252 249 251 259 272 275 299 302 334 342 355 359 371 372 403 415 445 449 454 534 538 548 619 621 625 73 97 119 154 185 206 213 226 238 253 255 256 281 287 297 332 336 351 353 367 368 392 405 407 437 441 442 447 465 466 479 494 508 511 566 572 584 46 54 57 58 59 68 71 83 117 125 218 219 262 264 268 270 319 343 347 360 397 411 413 429 432 435 460 467 470 471 475 531 545 564 573 579 603 608 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";

#endif //VGG_EXAMPLE_SCENE_H
