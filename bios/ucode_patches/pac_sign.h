unsigned long addr = 0x7c00;
unsigned long hook_address = 0x0c40;
unsigned long hook_entry = 0x01;
unsigned long ucode_patch[][4] = {
    // U7c00: tmp0:= ZEROEXT_DSZ64(0x1122); tmp0:= SHL_DSZ64(tmp0, 0x10); tmp0:= OR_DSZ64(tmp0, 0x3344)
    {0x804822470008, 0x406410030230, 0x4041444f0270, 0x300000c0},
    // U7c04: tmp0:= SHL_DSZ64(tmp0, 0x10); tmp0:= OR_DSZ64(tmp0, 0x5566); tmp0:= SHL_DSZ64(tmp0, 0x10)
    {0x406410030230, 0x4041665702b0, 0x406410030230, 0x300000c0},
    // U7c08: tmp0:= OR_DSZ64(tmp0, 0x7788); tmp1 := ZEROEXT_DSZ64(0x6575); tmp1 := XOR_DSZ64(tmp1, tmp0)
    {0x8041885f02f0, 0x80487517100b, 0x404600031c31, 0x300000c0},
    // U7c0c: tmp2 := ZEROEXT_DSZ64(0x6f6d); tmp2 := XOR_DSZ64(tmp2, rcx); tmp3 := ZEROEXT_DSZ64(0x7261)
    {0x80486d3f200b, 0x404600032872, 0xc048614b300b, 0x300000c0},
    // U7c10: tmp3 := XOR_DSZ64(tmp3, tmp0); tmp4 := ZEROEXT_DSZ64(0x6573); tmp4 := XOR_DSZ64(tmp4, rcx)
    {0x404600033c33, 0x40487317400b, 0x404600034874, 0x300000c0},
    // U7c14: tmp4 := XOR_DSZ64(tmp4, rax); tmp1 := ADD_DSZ64(tmp1, tmp2); tmp3 := ADD_DSZ64(tmp3, tmp4)
    {0x4600034834, 0x4000031cb1, 0xc04000033d33, 0x300000c0},
    // U7c18: tmp2 := ROL_DSZ64(tmp2, 0xd); tmp4 := ROL_DSZ64(tmp4, 0x10); tmp2 := XOR_DSZ64(tmp2, tmp1)
    {0x6c0d032232, 0xc06c10034234, 0x4600032c72, 0x300000c0},
    // U7c1c: tmp4 := XOR_DSZ64(tmp4, tmp3); tmp1 := ROL_DSZ64(tmp1, 0x20); tmp3 := ADD_DSZ64(tmp3, tmp2)
    {0x804600034cf4, 0x6c20031231, 0x4000033cb3, 0x300000c0},
    // U7c20: tmp1 := ADD_DSZ64(tmp1, tmp4); tmp2 := ROL_DSZ64(tmp2, 0x11); tmp4 := ROL_DSZ64(tmp4, 0x15)
    {0xc04000031d31, 0x806c11032232, 0xc06c15034234, 0x300000c0},
    // U7c24: tmp2 := XOR_DSZ64(tmp2, tmp3); tmp4 := XOR_DSZ64(tmp4, tmp1); tmp3 := ROL_DSZ64(tmp3, 0x20)
    {0x804600032cf2, 0x4600034c74, 0x6c20033233, 0x300000c0},
    // U7c28: tmp1 := XOR_DSZ64(tmp1, rax); tmp3 := XOR_DSZ64(tmp3, 0xff); tmp1 := ADD_DSZ64(tmp1, tmp2)
    {0x4600031831, 0x46ff033233, 0x4000031cb1, 0x300000c0},
    // U7c2c: tmp3 := ADD_DSZ64(tmp3, tmp4); tmp2 := ROL_DSZ64(tmp2, 0xd); tmp4 := ROL_DSZ64(tmp4, 0x10)
    {0xc04000033d33, 0x6c0d032232, 0xc06c10034234, 0x300000c0},
    // U7c30: tmp2 := XOR_DSZ64(tmp2, tmp1); tmp4 := XOR_DSZ64(tmp4, tmp3); tmp1 := ROL_DSZ64(tmp1, 0x20)
    {0x4600032c72, 0x804600034cf4, 0x6c20031231, 0x300000c0},
    // U7c34: tmp3 := ADD_DSZ64(tmp3, tmp2); tmp1 := ADD_DSZ64(tmp1, tmp4); tmp2 := ROL_DSZ64(tmp2, 0x11)
    {0x4000033cb3, 0xc04000031d31, 0x806c11032232, 0x300000c0},
    // U7c38: tmp4 := ROL_DSZ64(tmp4, 0x15); tmp2 := XOR_DSZ64(tmp2, tmp3); tmp4 := XOR_DSZ64(tmp4, tmp1)
    {0xc06c15034234, 0x804600032cf2, 0x4600034c74, 0x300000c0},
    // U7c3c: tmp3 := ROL_DSZ64(tmp3, 0x20); tmp5 := XOR_DSZ64(tmp1, tmp2); tmp5 := XOR_DSZ64(tmp5, tmp3)
    {0x6c20033233, 0x804600035cb1, 0x804600035cf5, 0x300000c0},
    // U7c40: tmp5 := XOR_DSZ64(tmp5, tmp4); tmp5 := SHL_DSZ64(tmp5, 0x30); rax := XOR_DSZ64(tmp5, rax) SEQW LFNCEWAIT, UEND0
    {0x4600035d35, 0xc06430035235, 0x404600020835, 0x130000f2},
};
