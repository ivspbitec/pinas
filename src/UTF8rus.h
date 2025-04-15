#pragma once
String UTF8rus(String source) {
  int i, k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };
  k = source.length(); i = 0;
  while (i < k) {
    n = source[i];
    if (n >= 0xC0) {
      switch (n) {
        case 0xD0:
          i++; n = source[i];
          if (n == 0x81) n = 0xA8;
          else if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
          break;
        case 0xD1:
          i++; n = source[i];
          if (n == 0x91) n = 0xB8;
          else if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
          break;
      }
    }
    m[0] = n;
    target += m;
    i++;
  }
  return target;
}
