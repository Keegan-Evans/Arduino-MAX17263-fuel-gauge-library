/*   
 max17263.ichgTerm = 0x0640; // 250mA on 10mΩ, leave default 
  max17263.vEmpty = 3.3; // leave default 

    float vEmpty;
     uint16_t ichgTerm;

  void setIchgTerm(uint16_t i);
  void setVEmpty(float vf);
  
  const uint8_t regLedCfg3     = 0x37; // not used
  const uint8_t regCustLED     = 0x64; // not used 

  setIchgTerm(ichgTerm); // leave default 
  setVEmpty(vEmpty); // leave default 

    const uint8_t regIchgTerm    = 0x1E; // Charge termination current default 0x0640 (250mA on 10mΩ) UG6597 page 29
  const uint8_t regVEmpty      = 0x3A; // 9bit, Empty voltage target, during load, 0...5.11V, default 3.3V UG6597 page 28

  void MAX17263::setIchgTerm(uint16_t i)
{ writeReg16Bit(regIchgTerm, i); // todo not tested
  Serial << "\nSet IchgTerm " << _HEX(readReg16Bit(regIchgTerm));
}

void MAX17263::setVEmpty(float vf) 
{ Serial << "\nVEmpty old " << _BIN(readReg16Bit(regVEmpty)); // default 0xA561 (3.3V/3.88V)
  uint16_t ve = vf*100;
  uint16_t val = readReg16Bit(regVEmpty);
  val &= 0x7F; // 0000.0000.0111.1111 leave VR page 16/37
  val |= ve << 7; // 3.3V = 330 = 101001010
  writeReg16Bit(regVEmpty, val); 
  Serial << "\nVEmpty new " << _BIN(readReg16Bit(regVEmpty));
}
*/
