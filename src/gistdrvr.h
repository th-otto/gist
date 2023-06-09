/*
 * Data of original driver (2248 bytes)
 * Consists of
 * -   28 byte GEMDOS header
 * - 1962 bytes of code
 * -  208 bytes of data
 * -   50 bytes of relocation info
 * + needs at least 424 bytes for BSS
 */
static char const driverdata[] = {
	0x60, 0x1a, 0x00, 0x00, 0x07, 0xaa, 0x00, 0x00, 0x00, 0xd0, 0x00, 0x00, 0x01, 0xa8, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x41, 0xfa, 0x00, 0x46,
	0x4a, 0x50, 0x66, 0x4e, 0x30, 0xbc, 0x00, 0x01, 0x41, 0xfa, 0xff, 0xf2, 0x20, 0x08, 0x22, 0x48,
	0x92, 0xfc, 0x00, 0x1c, 0xd1, 0xe9, 0x00, 0x02, 0xd1, 0xe9, 0x00, 0x06, 0x2f, 0x08, 0x2f, 0x29,
	0x00, 0x0a, 0xd1, 0xe9, 0x00, 0x0e, 0x22, 0x50, 0x4a, 0x98, 0x67, 0x1a, 0xd3, 0xc0, 0x42, 0x41,
	0xd1, 0x91, 0x12, 0x18, 0x67, 0x10, 0xd2, 0xc1, 0xb2, 0x7c, 0x00, 0x01, 0x66, 0xf2, 0xd2, 0xfc,
	0x00, 0xfd, 0x60, 0xee, 0x00, 0x00, 0x20, 0x1f, 0x20, 0x5f, 0x60, 0x02, 0x42, 0x18, 0x51, 0xc8,
	0xff, 0xfc, 0x4e, 0xf9, 0x00, 0x00, 0x00, 0x5c, 0x4e, 0x56, 0xff, 0xfc, 0x2e, 0xbc, 0x00, 0x00,
	0x06, 0xc0, 0x3f, 0x3c, 0x00, 0x26, 0x4e, 0xb9, 0x00, 0x00, 0x07, 0x7a, 0x54, 0x8f, 0x61, 0x20,
	0x4e, 0x5e, 0x4e, 0x75, 0x4e, 0x56, 0xff, 0xfc, 0x61, 0x16, 0x2e, 0xbc, 0x00, 0x00, 0x07, 0x1a,
	0x3f, 0x3c, 0x00, 0x26, 0x4e, 0xb9, 0x00, 0x00, 0x07, 0x7a, 0x54, 0x8f, 0x4e, 0x5e, 0x4e, 0x75,
	0x4e, 0x56, 0xff, 0xfa, 0x42, 0x6e, 0xff, 0xfe, 0x60, 0x0c, 0x3e, 0xae, 0xff, 0xfe, 0x61, 0x00,
	0x02, 0x00, 0x52, 0x6e, 0xff, 0xfe, 0x0c, 0x6e, 0x00, 0x03, 0xff, 0xfe, 0x6d, 0xec, 0x4e, 0x5e,
	0x4e, 0x75, 0x4e, 0x56, 0x00, 0x00, 0x48, 0xe7, 0x3f, 0x1c, 0x2a, 0x6e, 0x00, 0x08, 0x3e, 0x2e,
	0x00, 0x0c, 0x4a, 0x47, 0x6d, 0x06, 0xbe, 0x7c, 0x00, 0x02, 0x6f, 0x5e, 0x42, 0x47, 0x60, 0x02,
	0x52, 0x47, 0xbe, 0x7c, 0x00, 0x03, 0x6c, 0x14, 0x30, 0x07, 0xc1, 0xfc, 0x00, 0x8c, 0x20, 0x40,
	0x22, 0x7c, 0x00, 0x00, 0x08, 0x7e, 0x4a, 0x70, 0x98, 0x00, 0x66, 0xe4, 0xbe, 0x7c, 0x00, 0x03,
	0x66, 0x38, 0x30, 0x39, 0x00, 0x00, 0x08, 0xf0, 0xb0, 0x79, 0x00, 0x00, 0x09, 0x7c, 0x6c, 0x04,
	0x42, 0x40, 0x60, 0x02, 0x70, 0x01, 0x3e, 0x00, 0x30, 0x07, 0xc1, 0xfc, 0x00, 0x8c, 0x20, 0x40,
	0x22, 0x7c, 0x00, 0x00, 0x08, 0x7e, 0x30, 0x30, 0x98, 0x72, 0xb0, 0x79, 0x00, 0x00, 0x0a, 0x08,
	0x6c, 0x04, 0x30, 0x07, 0x60, 0x02, 0x70, 0x02, 0x3e, 0x00, 0x30, 0x07, 0xc1, 0xfc, 0x00, 0x8c,
	0x28, 0x40, 0xd9, 0xfc, 0x00, 0x00, 0x08, 0x7e, 0x30, 0x2c, 0x00, 0x72, 0xb0, 0x6e, 0x00, 0x12,
	0x6f, 0x06, 0x70, 0xff, 0x60, 0x00, 0x01, 0x50, 0x3e, 0x87, 0x61, 0x00, 0x01, 0x54, 0x36, 0x1d,
	0x66, 0x06, 0x30, 0x07, 0x60, 0x00, 0x01, 0x40, 0x30, 0x07, 0xc1, 0xfc, 0x00, 0x8c, 0x26, 0x40,
	0xd7, 0xfc, 0x00, 0x00, 0x08, 0x7e, 0x54, 0x8b, 0x7c, 0x01, 0x60, 0x04, 0x36, 0xdd, 0x52, 0x46,
	0xbc, 0x7c, 0x00, 0x38, 0x6d, 0xf6, 0x39, 0x6e, 0x00, 0x10, 0x00, 0x70, 0x39, 0x6e, 0x00, 0x12,
	0x00, 0x72, 0x42, 0x80, 0x29, 0x40, 0x00, 0x80, 0x29, 0x40, 0x00, 0x7c, 0x29, 0x40, 0x00, 0x88,
	0x29, 0x40, 0x00, 0x84, 0x29, 0x40, 0x00, 0x78, 0x29, 0x40, 0x00, 0x74, 0x4a, 0x6c, 0x00, 0x02,
	0x6d, 0x6c, 0x42, 0x45, 0x4a, 0x6e, 0x00, 0x10, 0x6d, 0x34, 0x60, 0x06, 0x04, 0x6e, 0x00, 0x0c,
	0x00, 0x10, 0x0c, 0x6e, 0x00, 0x6c, 0x00, 0x10, 0x6e, 0xf2, 0x60, 0x06, 0x06, 0x6e, 0x00, 0x0c,
	0x00, 0x10, 0x0c, 0x6e, 0x00, 0x18, 0x00, 0x10, 0x6d, 0xf2, 0x30, 0x6e, 0x00, 0x10, 0xd0, 0xfc,
	0xff, 0xe8, 0xd1, 0xc8, 0xd1, 0xfc, 0x00, 0x00, 0x07, 0xaa, 0x39, 0x50, 0x00, 0x02, 0x3e, 0xac,
	0x00, 0x02, 0x02, 0x57, 0x00, 0xff, 0x30, 0x07, 0xe3, 0x40, 0x3f, 0x00, 0x4e, 0xb9, 0x00, 0x00,
	0x07, 0x38, 0x54, 0x8f, 0x30, 0x2c, 0x00, 0x02, 0xe0, 0x40, 0x3e, 0x80, 0x30, 0x07, 0xe3, 0x40,
	0x3f, 0x00, 0x52, 0x57, 0x4e, 0xb9, 0x00, 0x00, 0x07, 0x38, 0x54, 0x8f, 0x60, 0x10, 0x7a, 0x01,
	0x30, 0x07, 0xe1, 0x65, 0x42, 0x80, 0x29, 0x40, 0x00, 0x3a, 0x39, 0x40, 0x00, 0x24, 0x4a, 0x6c,
	0x00, 0x04, 0x6d, 0x14, 0x42, 0x44, 0x3e, 0xac, 0x00, 0x04, 0x3f, 0x3c, 0x00, 0x06, 0x4e, 0xb9,
	0x00, 0x00, 0x07, 0x38, 0x54, 0x8f, 0x60, 0x10, 0x78, 0x08, 0x30, 0x07, 0xe1, 0x64, 0x42, 0x80,
	0x29, 0x40, 0x00, 0x66, 0x39, 0x40, 0x00, 0x50, 0x30, 0x47, 0xd1, 0xc8, 0x22, 0x7c, 0x00, 0x00,
	0x08, 0x54, 0x3e, 0xb0, 0x98, 0x00, 0x3f, 0x05, 0x30, 0x04, 0x81, 0x57, 0x3f, 0x3c, 0x00, 0x07,
	0x4e, 0xb9, 0x00, 0x00, 0x07, 0x38, 0x58, 0x8f, 0x4a, 0x6e, 0x00, 0x0e, 0x6d, 0x06, 0x39, 0x6e,
	0x00, 0x0e, 0x00, 0x06, 0x4a, 0x6c, 0x00, 0x08, 0x66, 0x18, 0x29, 0x7c, 0x00, 0x0f, 0x00, 0x00,
	0x00, 0x74, 0x3e, 0xac, 0x00, 0x06, 0x3f, 0x07, 0x50, 0x57, 0x4e, 0xb9, 0x00, 0x00, 0x07, 0x38,
	0x54, 0x8f, 0x38, 0x83, 0x30, 0x07, 0x4a, 0x9f, 0x4c, 0xdf, 0x38, 0xf8, 0x4e, 0x5e, 0x4e, 0x75,
	0x4e, 0x56, 0xff, 0xfc, 0x4a, 0x6e, 0x00, 0x08, 0x6d, 0x40, 0x0c, 0x6e, 0x00, 0x02, 0x00, 0x08,
	0x6e, 0x38, 0x30, 0x2e, 0x00, 0x08, 0xc1, 0xfc, 0x00, 0x8c, 0xd0, 0xbc, 0x00, 0x00, 0x08, 0x7e,
	0x20, 0x40, 0x70, 0x00, 0x31, 0x40, 0x00, 0x72, 0x32, 0x2e, 0x00, 0x08, 0xc3, 0xfc, 0x00, 0x8c,
	0xd2, 0xbc, 0x00, 0x00, 0x08, 0x7e, 0x22, 0x41, 0x32, 0x80, 0x42, 0x57, 0x3f, 0x2e, 0x00, 0x08,
	0x50, 0x57, 0x4e, 0xb9, 0x00, 0x00, 0x07, 0x38, 0x54, 0x8f, 0x4e, 0x5e, 0x4e, 0x75, 0x4e, 0x56,
	0xff, 0xfc, 0x4a, 0x6e, 0x00, 0x08, 0x6d, 0x48, 0x0c, 0x6e, 0x00, 0x02, 0x00, 0x08, 0x6e, 0x40,
	0x30, 0x2e, 0x00, 0x08, 0xc1, 0xfc, 0x00, 0x8c, 0x20, 0x40, 0x22, 0x7c, 0x00, 0x00, 0x08, 0x7e,
	0x4a, 0x70, 0x98, 0x00, 0x67, 0x2a, 0x30, 0x2e, 0x00, 0x08, 0xc1, 0xfc, 0x00, 0x8c, 0xd0, 0xbc,
	0x00, 0x00, 0x08, 0x7e, 0x20, 0x40, 0x30, 0xbc, 0x00, 0x01, 0x30, 0x2e, 0x00, 0x08, 0xc1, 0xfc,
	0x00, 0x8c, 0xd0, 0xbc, 0x00, 0x00, 0x08, 0x7e, 0x20, 0x40, 0x31, 0x7c, 0xff, 0xff, 0x00, 0x70,
	0x4e, 0x5e, 0x4e, 0x75, 0x4e, 0x56, 0xff, 0xfc, 0x30, 0x2e, 0x00, 0x08, 0xc1, 0xfc, 0x00, 0x8c,
	0x20, 0x40, 0x22, 0x7c, 0x00, 0x00, 0x08, 0x7e, 0x30, 0x30, 0x98, 0x72, 0x4e, 0x5e, 0x4e, 0x75,
	0x48, 0xe7, 0xf0, 0xe0, 0x24, 0x79, 0x00, 0x00, 0x07, 0x10, 0x20, 0x79, 0x00, 0x00, 0x07, 0x14,
	0x22, 0x7c, 0xff, 0xff, 0x88, 0x00, 0x74, 0x02, 0x40, 0xe7, 0x00, 0x7c, 0x05, 0x00, 0x02, 0x7c,
	0xfd, 0xff, 0x13, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x04, 0x84, 0x4a, 0x50, 0x67, 0x00, 0x03, 0x00,
	0x30, 0x28, 0x00, 0x08, 0x22, 0x28, 0x00, 0x74, 0xb0, 0x3c, 0x00, 0x01, 0x66, 0x18, 0xd2, 0xa8,
	0x00, 0x0a, 0xb2, 0xbc, 0x00, 0x0f, 0x00, 0x00, 0x6d, 0x3e, 0x22, 0x3c, 0x00, 0x0f, 0x00, 0x00,
	0x52, 0x68, 0x00, 0x08, 0x60, 0x32, 0xb0, 0x3c, 0x00, 0x02, 0x66, 0x14, 0xd2, 0xa8, 0x00, 0x0e,
	0xb2, 0xa8, 0x00, 0x12, 0x6e, 0x22, 0x22, 0x28, 0x00, 0x12, 0x52, 0x68, 0x00, 0x08, 0x60, 0x18,
	0xb0, 0x3c, 0x00, 0x04, 0x66, 0x16, 0xd2, 0xa8, 0x00, 0x16, 0x4a, 0x81, 0x6e, 0x0a, 0x72, 0x00,
	0x31, 0x41, 0x00, 0x08, 0x30, 0xbc, 0x00, 0x01, 0x21, 0x41, 0x00, 0x74, 0x20, 0x28, 0x00, 0x1a,
	0x67, 0x28, 0x4a, 0x68, 0x00, 0x22, 0x67, 0x06, 0x53, 0x68, 0x00, 0x22, 0x60, 0x1c, 0x22, 0x28,
	0x00, 0x78, 0xd2, 0xa8, 0x00, 0x1e, 0xb2, 0x80, 0x6c, 0x06, 0x44, 0x80, 0xb2, 0x80, 0x6e, 0x06,
	0x22, 0x00, 0x44, 0xa8, 0x00, 0x1e, 0x21, 0x41, 0x00, 0x78, 0x30, 0x28, 0x00, 0x08, 0x80, 0x68,
	0x00, 0x1a, 0x67, 0x30, 0x30, 0x28, 0x00, 0x06, 0xd0, 0x40, 0x30, 0x32, 0x00, 0x00, 0x22, 0x28,
	0x00, 0x74, 0xd2, 0xa8, 0x00, 0x78, 0x6a, 0x04, 0x70, 0x00, 0x60, 0x0e, 0xe0, 0x81, 0xc1, 0xc1,
	0x48, 0x40, 0xb0, 0x7c, 0x00, 0x0f, 0x6f, 0x02, 0x70, 0x0f, 0x12, 0x02, 0x50, 0x01, 0x12, 0x81,
	0x13, 0x40, 0x00, 0x02, 0x30, 0x28, 0x00, 0x24, 0x22, 0x28, 0x00, 0x7c, 0xb0, 0x3c, 0x00, 0x01,
	0x66, 0x22, 0xd2, 0xa8, 0x00, 0x26, 0x4a, 0x68, 0x00, 0x26, 0x6b, 0x08, 0xb2, 0xa8, 0x00, 0x2a,
	0x6d, 0x56, 0x60, 0x06, 0xb2, 0xa8, 0x00, 0x2a, 0x6e, 0x4e, 0x22, 0x28, 0x00, 0x2a, 0x52, 0x68,
	0x00, 0x24, 0x60, 0x44, 0xb0, 0x3c, 0x00, 0x02, 0x66, 0x22, 0xd2, 0xa8, 0x00, 0x2e, 0x4a, 0x68,
	0x00, 0x2e, 0x6b, 0x08, 0xb2, 0xa8, 0x00, 0x32, 0x6d, 0x2e, 0x60, 0x06, 0xb2, 0xa8, 0x00, 0x32,
	0x6e, 0x26, 0x22, 0x28, 0x00, 0x32, 0x52, 0x68, 0x00, 0x24, 0x60, 0x1c, 0xb0, 0x3c, 0x00, 0x04,
	0x66, 0x1a, 0xd2, 0xa8, 0x00, 0x36, 0x4a, 0x68, 0x00, 0x36, 0x6b, 0x06, 0x4a, 0x81, 0x6b, 0x08,
	0x60, 0x04, 0x4a, 0x81, 0x6e, 0x02, 0x72, 0x00, 0x21, 0x41, 0x00, 0x7c, 0x20, 0x28, 0x00, 0x3a,
	0x67, 0x42, 0x4a, 0x68, 0x00, 0x4e, 0x67, 0x06, 0x53, 0x68, 0x00, 0x4e, 0x60, 0x36, 0x22, 0x28,
	0x00, 0x3e, 0x6b, 0x12, 0xd2, 0xa8, 0x00, 0x80, 0x64, 0x06, 0x21, 0x68, 0x00, 0x42, 0x00, 0x3e,
	0xb2, 0x80, 0x6d, 0x1c, 0x60, 0x14, 0x20, 0x28, 0x00, 0x46, 0xd2, 0xa8, 0x00, 0x80, 0x65, 0x06,
	0x21, 0x68, 0x00, 0x4a, 0x00, 0x3e, 0xb2, 0x80, 0x6e, 0x06, 0x22, 0x00, 0x44, 0xa8, 0x00, 0x3e,
	0x21, 0x41, 0x00, 0x80, 0x30, 0x28, 0x00, 0x24, 0x80, 0x68, 0x00, 0x3a, 0x67, 0x3e, 0x20, 0x28,
	0x00, 0x80, 0xd0, 0xa8, 0x00, 0x7c, 0x48, 0x40, 0xc1, 0xe8, 0x00, 0x02, 0xe9, 0x80, 0x48, 0x40,
	0x6a, 0x02, 0x52, 0x40, 0xd0, 0x68, 0x00, 0x02, 0x6a, 0x04, 0x70, 0x00, 0x60, 0x0a, 0xb0, 0x7c,
	0x0f, 0xff, 0x6f, 0x04, 0x30, 0x3c, 0x0f, 0xff, 0x12, 0x02, 0xd2, 0x01, 0x12, 0x81, 0x13, 0x40,
	0x00, 0x02, 0x52, 0x01, 0x12, 0x81, 0xe0, 0x40, 0x13, 0x40, 0x00, 0x02, 0x30, 0x28, 0x00, 0x50,
	0x22, 0x28, 0x00, 0x84, 0xb0, 0x3c, 0x00, 0x01, 0x66, 0x22, 0xd2, 0xa8, 0x00, 0x52, 0x4a, 0x68,
	0x00, 0x52, 0x6b, 0x08, 0xb2, 0xa8, 0x00, 0x56, 0x6d, 0x56, 0x60, 0x06, 0xb2, 0xa8, 0x00, 0x56,
	0x6e, 0x4e, 0x22, 0x28, 0x00, 0x56, 0x52, 0x68, 0x00, 0x50, 0x60, 0x44, 0xb0, 0x3c, 0x00, 0x02,
	0x66, 0x22, 0xd2, 0xa8, 0x00, 0x5a, 0x4a, 0x68, 0x00, 0x5a, 0x6b, 0x08, 0xb2, 0xa8, 0x00, 0x5e,
	0x6d, 0x2e, 0x60, 0x06, 0xb2, 0xa8, 0x00, 0x5e, 0x6e, 0x26, 0x22, 0x28, 0x00, 0x5e, 0x52, 0x68,
	0x00, 0x50, 0x60, 0x1c, 0xb0, 0x3c, 0x00, 0x04, 0x66, 0x1a, 0xd2, 0xa8, 0x00, 0x62, 0x4a, 0x68,
	0x00, 0x62, 0x6b, 0x06, 0x4a, 0x81, 0x6b, 0x08, 0x60, 0x04, 0x4a, 0x81, 0x6e, 0x02, 0x72, 0x00,
	0x21, 0x41, 0x00, 0x84, 0x20, 0x28, 0x00, 0x66, 0x67, 0x28, 0x4a, 0x68, 0x00, 0x6e, 0x67, 0x06,
	0x53, 0x68, 0x00, 0x6e, 0x60, 0x1c, 0x22, 0x28, 0x00, 0x88, 0xd2, 0xa8, 0x00, 0x6a, 0xb2, 0x80,
	0x6c, 0x06, 0x44, 0x80, 0xb2, 0x80, 0x6e, 0x06, 0x22, 0x00, 0x44, 0xa8, 0x00, 0x6a, 0x21, 0x41,
	0x00, 0x88, 0x30, 0x28, 0x00, 0x50, 0x80, 0x68, 0x00, 0x66, 0x67, 0x24, 0x20, 0x28, 0x00, 0x88,
	0xd0, 0xa8, 0x00, 0x84, 0x48, 0x40, 0xd0, 0x68, 0x00, 0x04, 0x6a, 0x04, 0x70, 0x00, 0x60, 0x08,
	0xb0, 0x3c, 0x00, 0x1f, 0x6f, 0x02, 0x70, 0x1f, 0x12, 0xbc, 0x00, 0x06, 0x13, 0x40, 0x00, 0x02,
	0x4a, 0x68, 0x00, 0x70, 0x6a, 0x58, 0x53, 0x50, 0x66, 0x54, 0x42, 0x68, 0x00, 0x72, 0x4a, 0x68,
	0x00, 0x08, 0x66, 0x0e, 0x12, 0x02, 0x50, 0x41, 0x12, 0x81, 0x13, 0x7c, 0x00, 0x00, 0x00, 0x02,
	0x60, 0x3c, 0x53, 0x50, 0x70, 0x04, 0x31, 0x40, 0x00, 0x08, 0x4a, 0x68, 0x00, 0x24, 0x67, 0x14,
	0x31, 0x40, 0x00, 0x24, 0x32, 0x28, 0x00, 0x36, 0x36, 0x28, 0x00, 0x7c, 0xb3, 0x43, 0x6b, 0x04,
	0x44, 0xa8, 0x00, 0x36, 0x4a, 0x68, 0x00, 0x50, 0x67, 0x14, 0x31, 0x40, 0x00, 0x50, 0x32, 0x28,
	0x00, 0x62, 0x36, 0x28, 0x00, 0x84, 0xb3, 0x43, 0x6b, 0x04, 0x44, 0xa8, 0x00, 0x62, 0x41, 0xe8,
	0xff, 0x74, 0x51, 0xca, 0xfc, 0xf6, 0x30, 0x28, 0x00, 0x8c, 0x80, 0x68, 0x01, 0x18, 0x80, 0x68,
	0x01, 0xa4, 0x66, 0x0a, 0x13, 0xf9, 0x00, 0x00, 0x07, 0x18, 0x00, 0x00, 0x04, 0x84, 0x46, 0xdf,
	0x4c, 0xdf, 0x07, 0x0f, 0x2f, 0x39, 0x00, 0x00, 0x07, 0x0c, 0x4e, 0x75, 0x48, 0xe7, 0x00, 0xc0,
	0x41, 0xf9, 0x00, 0x00, 0x07, 0x0c, 0x20, 0xf9, 0x00, 0x00, 0x01, 0x14, 0x43, 0xf9, 0x00, 0x00,
	0x08, 0x5a, 0x20, 0xc9, 0x43, 0xf9, 0x00, 0x00, 0x09, 0x96, 0x20, 0xc9, 0x10, 0xb9, 0x00, 0x00,
	0x04, 0x84, 0x41, 0xf9, 0x00, 0x00, 0x07, 0x48, 0x23, 0xc8, 0x00, 0x00, 0x00, 0xa4, 0x41, 0xf9,
	0x00, 0x00, 0x03, 0x64, 0x23, 0xc8, 0x00, 0x00, 0x01, 0x14, 0x13, 0xfc, 0x00, 0x40, 0xff, 0xff,
	0xfa, 0x17, 0x4c, 0xdf, 0x03, 0x00, 0x4e, 0x75, 0x4e, 0x71, 0x4e, 0x71, 0x4e, 0x71, 0x4e, 0x71,
	0x4e, 0x71, 0x4e, 0x71, 0x4e, 0x71, 0x23, 0xf9, 0x00, 0x00, 0x07, 0x0c, 0x00, 0x00, 0x01, 0x14,
	0x13, 0xf9, 0x00, 0x00, 0x07, 0x18, 0x00, 0x00, 0x04, 0x84, 0x13, 0xfc, 0x00, 0x48, 0xff, 0xff,
	0xfa, 0x17, 0x4e, 0x75, 0x32, 0x2f, 0x00, 0x04, 0x30, 0x2f, 0x00, 0x06, 0x34, 0x2f, 0x00, 0x08,
	0x4e, 0x49, 0x4e, 0x75, 0x40, 0xe7, 0x00, 0x7c, 0x07, 0x00, 0x20, 0x7c, 0xff, 0xff, 0x88, 0x00,
	0xc2, 0x3c, 0x00, 0x0f, 0x10, 0x81, 0x4a, 0x40, 0x6b, 0x10, 0xb2, 0x3c, 0x00, 0x07, 0x66, 0x06,
	0x12, 0x10, 0xc2, 0x02, 0x80, 0x01, 0x11, 0x40, 0x00, 0x02, 0x70, 0x00, 0x10, 0x10, 0x10, 0xbc,
	0x00, 0x0b, 0x46, 0xdf, 0x4e, 0x73, 0x23, 0xdf, 0x00, 0x00, 0x08, 0x7a, 0x4e, 0x4e, 0x2f, 0x39,
	0x00, 0x00, 0x08, 0x7a, 0x4e, 0x75, 0x23, 0xdf, 0x00, 0x00, 0x08, 0x7a, 0x4e, 0x4d, 0x2f, 0x39,
	0x00, 0x00, 0x08, 0x7a, 0x4e, 0x75, 0x23, 0xdf, 0x00, 0x00, 0x08, 0x7a, 0x4e, 0x41, 0x2f, 0x39,
	0x00, 0x00, 0x08, 0x7a, 0x4e, 0x75, 0x0e, 0xee, 0x0e, 0x18, 0x0d, 0x4d, 0x0c, 0x8e, 0x0b, 0xda,
	0x0b, 0x2f, 0x0a, 0x8f, 0x09, 0xf7, 0x09, 0x68, 0x08, 0xe1, 0x08, 0x61, 0x07, 0xe9, 0x07, 0x77,
	0x07, 0x0c, 0x06, 0xa7, 0x06, 0x47, 0x05, 0xed, 0x05, 0x98, 0x05, 0x47, 0x04, 0xfc, 0x04, 0xb4,
	0x04, 0x70, 0x04, 0x31, 0x03, 0xf4, 0x03, 0xbc, 0x03, 0x86, 0x03, 0x53, 0x03, 0x24, 0x02, 0xf6,
	0x02, 0xcc, 0x02, 0xa4, 0x02, 0x7e, 0x02, 0x5a, 0x02, 0x38, 0x02, 0x18, 0x01, 0xfa, 0x01, 0xde,
	0x01, 0xc3, 0x01, 0xaa, 0x01, 0x92, 0x01, 0x7b, 0x01, 0x66, 0x01, 0x52, 0x01, 0x3f, 0x01, 0x2d,
	0x01, 0x1c, 0x01, 0x0c, 0x00, 0xfd, 0x00, 0xef, 0x00, 0xe1, 0x00, 0xd5, 0x00, 0xc9, 0x00, 0xbe,
	0x00, 0xb3, 0x00, 0xa9, 0x00, 0x9f, 0x00, 0x96, 0x00, 0x8e, 0x00, 0x86, 0x00, 0x7f, 0x00, 0x77,
	0x00, 0x71, 0x00, 0x6a, 0x00, 0x64, 0x00, 0x5f, 0x00, 0x59, 0x00, 0x54, 0x00, 0x50, 0x00, 0x4b,
	0x00, 0x47, 0x00, 0x43, 0x00, 0x3f, 0x00, 0x3c, 0x00, 0x38, 0x00, 0x35, 0x00, 0x32, 0x00, 0x2f,
	0x00, 0x2d, 0x00, 0x2a, 0x00, 0x28, 0x00, 0x26, 0x00, 0x24, 0x00, 0x22, 0x00, 0x20, 0x00, 0x1e,
	0x00, 0xf6, 0x00, 0xed, 0x00, 0xdb, 0x00, 0x00, 0x00, 0x12, 0x00, 0x23, 0x00, 0x34, 0x00, 0x45,
	0x00, 0x56, 0x00, 0x67, 0x00, 0x78, 0x00, 0x89, 0x00, 0x9a, 0x00, 0xab, 0x00, 0xbc, 0x00, 0xcd,
	0x00, 0xde, 0x00, 0xef, 0x01, 0x00, 0x00, 0x00, 0x00, 0x58, 0x0a, 0x0a, 0x14, 0x0a, 0x5c, 0x12,
	0x06, 0x18, 0x0a, 0x18, 0x2e, 0x74, 0x18, 0x18, 0x2a, 0x1e, 0x14, 0x2a, 0x30, 0x16, 0x12, 0x28,
	0x14, 0x14, 0x20, 0x12, 0x06, 0x01, 0x01, 0x01, 0x40, 0x10, 0x0c, 0x0c, 0x08, 0x0e, 0x0c, 0x28,
	0x0a, 0x56, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
