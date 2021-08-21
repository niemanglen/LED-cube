CHSV HColor(byte h){
  return CHSV(h,255,brightness);
}

CHSV HColor(byte h, byte s){
  return CHSV(h,s,brightness);
}

CHSV HColor(byte h, byte s, byte v){
  return CHSV(h,s,v);
}


CHSV DColor(byte h, byte hu) {
  if (h==0){
    return CHSV(hu,0,0);
  }else if (h==1){
    return CHSV(hu,150,100);
  }else if (h==2){
    return CHSV(hu,200,100);
  }else if(h==3) {
    return CHSV(hu,250,100);
  }
}

CRGB HeaColor(byte h){
  return HeatColor(h);
}
