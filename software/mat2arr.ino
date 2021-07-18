void mat2arr(byte led_array[], byte input_mat[16][8]) {

  //this loop handles the leds on all of the faces that are not the top and the bottom
  for (byte i=2;i<6;i++){
    for (byte j=0;j<4;j++){
      for (byte k=0;k<4;k++){
        led_array[16+4*(i-2)+j + 16*k] = input_mat[j+4*k][i];
      }
    }
  }

  //top
  led_array[14] = input_mat[1][6];
  led_array[13] = input_mat[2][6];
  
  led_array[11] = input_mat[14][6];
  led_array[7] = input_mat[13][6];

  led_array[8] = input_mat[5][6];
  led_array[4] = input_mat[6][6];

  led_array[2] = input_mat[10][6];
  led_array[1] = input_mat[9][6];


  led_array[15] = input_mat[0][6];
  led_array[12] = input_mat[4][6];
  led_array[3] = input_mat[12][6];
  led_array[0] = input_mat[8][6];

  led_array[10] = input_mat[14][7];
  led_array[9] = input_mat[2][7];
  led_array[6] = input_mat[10][7];
  led_array[5] = input_mat[6][7];


  //bottom
  led_array[93] = input_mat[1][1];
  led_array[94] = input_mat[2][1];

  led_array[91] = input_mat[5][1];
  led_array[87] = input_mat[6][1];

  led_array[82] = input_mat[9][1];
  led_array[81] = input_mat[10][1];

  led_array[84] = input_mat[13][1];
  led_array[88] = input_mat[14][1];

  led_array[92] = input_mat[15][1];
  led_array[95] = input_mat[3][1];
  led_array[83] = input_mat[7][1];
  led_array[80] = input_mat[11][1];

  led_array[89] = input_mat[1][0];
  led_array[90] = input_mat[5][0];
  led_array[86] = input_mat[9][0];
  led_array[85] = input_mat[13][0];

  

  
  
}
