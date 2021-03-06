#ifndef _HTTP_CREDENTIAL_H_
#define _HTTP_CREDENTIAL_H_

/* extern const uint8_t cert_der_start[] asm("_binary_cert_der_start"); */

/*
static const char rsa_private_key_der[] = {
        #include "key.der"
};

static const char x509_public_certificate_der[] = {
        #include "cert.der"
};
*/
static const char x509_public_certificate_rsa1024_der[] = {
        0x30, 0x82, 0x02, 0xd4, 0x30, 0x82, 0x02, 0x3d,
        0xa0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x14, 0x37,
        0x90, 0x66, 0x1b, 0x06, 0x45, 0x14, 0x45, 0x2e,
        0x0b, 0x18, 0x54, 0x25, 0xfc, 0x9c, 0x33, 0x3e,
        0x60, 0x7b, 0xd2, 0x30, 0x0d, 0x06, 0x09, 0x2a,
        0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0b,
        0x05, 0x00, 0x30, 0x7c, 0x31, 0x0b, 0x30, 0x09,
        0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x46,
        0x52, 0x31, 0x13, 0x30, 0x11, 0x06, 0x03, 0x55,
        0x04, 0x08, 0x0c, 0x0a, 0x53, 0x6f, 0x6d, 0x65,
        0x2d, 0x53, 0x74, 0x61, 0x74, 0x65, 0x31, 0x12,
        0x30, 0x10, 0x06, 0x03, 0x55, 0x04, 0x07, 0x0c,
        0x09, 0x4b, 0x6f, 0x67, 0x65, 0x6e, 0x68, 0x65,
        0x69, 0x6d, 0x31, 0x21, 0x30, 0x1f, 0x06, 0x03,
        0x55, 0x04, 0x0a, 0x0c, 0x18, 0x49, 0x6e, 0x74,
        0x65, 0x72, 0x6e, 0x65, 0x74, 0x20, 0x57, 0x69,
        0x64, 0x67, 0x69, 0x74, 0x73, 0x20, 0x50, 0x74,
        0x79, 0x20, 0x4c, 0x74, 0x64, 0x31, 0x21, 0x30,
        0x1f, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7,
        0x0d, 0x01, 0x09, 0x01, 0x16, 0x12, 0x6c, 0x64,
        0x2e, 0x61, 0x64, 0x65, 0x63, 0x79, 0x40, 0x67,
        0x6d, 0x61, 0x69, 0x6c, 0x2e, 0x63, 0x6f, 0x6d,
        0x30, 0x1e, 0x17, 0x0d, 0x32, 0x31, 0x31, 0x31,
        0x31, 0x36, 0x32, 0x32, 0x30, 0x36, 0x30, 0x35,
        0x5a, 0x17, 0x0d, 0x32, 0x32, 0x31, 0x31, 0x31,
        0x36, 0x32, 0x32, 0x30, 0x36, 0x30, 0x35, 0x5a,
        0x30, 0x7c, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03,
        0x55, 0x04, 0x06, 0x13, 0x02, 0x46, 0x52, 0x31,
        0x13, 0x30, 0x11, 0x06, 0x03, 0x55, 0x04, 0x08,
        0x0c, 0x0a, 0x53, 0x6f, 0x6d, 0x65, 0x2d, 0x53,
        0x74, 0x61, 0x74, 0x65, 0x31, 0x12, 0x30, 0x10,
        0x06, 0x03, 0x55, 0x04, 0x07, 0x0c, 0x09, 0x4b,
        0x6f, 0x67, 0x65, 0x6e, 0x68, 0x65, 0x69, 0x6d,
        0x31, 0x21, 0x30, 0x1f, 0x06, 0x03, 0x55, 0x04,
        0x0a, 0x0c, 0x18, 0x49, 0x6e, 0x74, 0x65, 0x72,
        0x6e, 0x65, 0x74, 0x20, 0x57, 0x69, 0x64, 0x67,
        0x69, 0x74, 0x73, 0x20, 0x50, 0x74, 0x79, 0x20,
        0x4c, 0x74, 0x64, 0x31, 0x21, 0x30, 0x1f, 0x06,
        0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01,
        0x09, 0x01, 0x16, 0x12, 0x6c, 0x64, 0x2e, 0x61,
        0x64, 0x65, 0x63, 0x79, 0x40, 0x67, 0x6d, 0x61,
        0x69, 0x6c, 0x2e, 0x63, 0x6f, 0x6d, 0x30, 0x81,
        0x9f, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48,
        0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05, 0x00,
        0x03, 0x81, 0x8d, 0x00, 0x30, 0x81, 0x89, 0x02,
        0x81, 0x81, 0x00, 0x9a, 0x3b, 0x1a, 0xfb, 0xc6,
        0xe8, 0xfe, 0x50, 0xf6, 0xe9, 0x15, 0xa3, 0x06,
        0xd4, 0xe4, 0x57, 0xa9, 0xa8, 0xa9, 0xdf, 0xb2,
        0xb0, 0x5b, 0xa8, 0xbd, 0x6a, 0xd7, 0xf7, 0x54,
        0x17, 0x93, 0xe9, 0x67, 0x1d, 0x6e, 0x35, 0xff,
        0x8d, 0x81, 0x85, 0x2a, 0x8f, 0x96, 0x29, 0xb4,
        0xf4, 0x1b, 0xd2, 0xa3, 0x9e, 0x28, 0x67, 0xfb,
        0x65, 0x3b, 0xde, 0xfc, 0x9a, 0xfc, 0x9b, 0x41,
        0xbe, 0x67, 0x9a, 0x80, 0xc5, 0xb2, 0xee, 0xf1,
        0x76, 0x6b, 0x69, 0x3a, 0x9e, 0x4b, 0x62, 0xba,
        0xbd, 0x7f, 0x66, 0xbf, 0x17, 0x61, 0xf8, 0xc1,
        0xce, 0x03, 0xb5, 0xd3, 0xb1, 0x3c, 0xe6, 0xa2,
        0x45, 0xd2, 0x4a, 0x3f, 0x4a, 0x8e, 0xcc, 0x7b,
        0x2a, 0x0c, 0xf8, 0xef, 0xd1, 0xa2, 0x0e, 0x66,
        0x5d, 0x1e, 0x15, 0x18, 0x9f, 0xa5, 0x1d, 0x3e,
        0xe5, 0x74, 0xb8, 0xc7, 0x93, 0x85, 0x67, 0x5b,
        0xae, 0x93, 0x7b, 0x02, 0x03, 0x01, 0x00, 0x01,
        0xa3, 0x53, 0x30, 0x51, 0x30, 0x1d, 0x06, 0x03,
        0x55, 0x1d, 0x0e, 0x04, 0x16, 0x04, 0x14, 0xe0,
        0xfb, 0x33, 0x15, 0x10, 0xa6, 0x8d, 0x13, 0x3e,
        0xef, 0xf0, 0x4b, 0x0c, 0x92, 0x05, 0x7c, 0xef,
        0x30, 0x13, 0x6e, 0x30, 0x1f, 0x06, 0x03, 0x55,
        0x1d, 0x23, 0x04, 0x18, 0x30, 0x16, 0x80, 0x14,
        0xe0, 0xfb, 0x33, 0x15, 0x10, 0xa6, 0x8d, 0x13,
        0x3e, 0xef, 0xf0, 0x4b, 0x0c, 0x92, 0x05, 0x7c,
        0xef, 0x30, 0x13, 0x6e, 0x30, 0x0f, 0x06, 0x03,
        0x55, 0x1d, 0x13, 0x01, 0x01, 0xff, 0x04, 0x05,
        0x30, 0x03, 0x01, 0x01, 0xff, 0x30, 0x0d, 0x06,
        0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01,
        0x01, 0x0b, 0x05, 0x00, 0x03, 0x81, 0x81, 0x00,
        0x5c, 0x3e, 0x76, 0x1e, 0x21, 0x92, 0xb3, 0xe4,
        0x5d, 0x3a, 0x33, 0x69, 0x8b, 0xca, 0xf5, 0x41,
        0x10, 0xdd, 0x5f, 0x0e, 0xa5, 0x9b, 0x41, 0x74,
        0x11, 0xba, 0x86, 0x26, 0x54, 0x37, 0xf5, 0x9b,
        0xfe, 0x7e, 0x1c, 0x68, 0x9e, 0x85, 0x59, 0xca,
        0x17, 0x0c, 0x8f, 0xd1, 0xfc, 0x4a, 0xc8, 0x63,
        0x3e, 0x25, 0xd7, 0xf9, 0xd8, 0x41, 0xac, 0xc4,
        0x84, 0x8e, 0xd1, 0x25, 0x01, 0xa4, 0x58, 0xee,
        0xad, 0x50, 0x67, 0x8d, 0x4b, 0x4c, 0x28, 0x26,
        0x09, 0xba, 0x05, 0xbc, 0x0b, 0xd3, 0x6a, 0x38,
        0xf9, 0xc8, 0xbb, 0x35, 0x5c, 0xcd, 0xab, 0x4b,
        0x83, 0x94, 0x1e, 0xaa, 0x97, 0xcf, 0x66, 0x38,
        0x4b, 0x30, 0x11, 0x75, 0xa1, 0x43, 0x19, 0x92,
        0xd4, 0xea, 0xf5, 0x2b, 0x56, 0x6d, 0x94, 0xcc,
        0x1f, 0xf0, 0x09, 0x6c, 0x0f, 0x36, 0xdc, 0xc2,
        0x60, 0x87, 0x72, 0x79, 0xfc, 0xd0, 0xf7, 0xd8,
        };
static const char rsa_private_key_rsa1024_der[] = {
        0x30, 0x82, 0x02, 0x5c, 0x02, 0x01, 0x00, 0x02,
        0x81, 0x81, 0x00, 0x9a, 0x3b, 0x1a, 0xfb, 0xc6,
        0xe8, 0xfe, 0x50, 0xf6, 0xe9, 0x15, 0xa3, 0x06,
        0xd4, 0xe4, 0x57, 0xa9, 0xa8, 0xa9, 0xdf, 0xb2,
        0xb0, 0x5b, 0xa8, 0xbd, 0x6a, 0xd7, 0xf7, 0x54,
        0x17, 0x93, 0xe9, 0x67, 0x1d, 0x6e, 0x35, 0xff,
        0x8d, 0x81, 0x85, 0x2a, 0x8f, 0x96, 0x29, 0xb4,
        0xf4, 0x1b, 0xd2, 0xa3, 0x9e, 0x28, 0x67, 0xfb,
        0x65, 0x3b, 0xde, 0xfc, 0x9a, 0xfc, 0x9b, 0x41,
        0xbe, 0x67, 0x9a, 0x80, 0xc5, 0xb2, 0xee, 0xf1,
        0x76, 0x6b, 0x69, 0x3a, 0x9e, 0x4b, 0x62, 0xba,
        0xbd, 0x7f, 0x66, 0xbf, 0x17, 0x61, 0xf8, 0xc1,
        0xce, 0x03, 0xb5, 0xd3, 0xb1, 0x3c, 0xe6, 0xa2,
        0x45, 0xd2, 0x4a, 0x3f, 0x4a, 0x8e, 0xcc, 0x7b,
        0x2a, 0x0c, 0xf8, 0xef, 0xd1, 0xa2, 0x0e, 0x66,
        0x5d, 0x1e, 0x15, 0x18, 0x9f, 0xa5, 0x1d, 0x3e,
        0xe5, 0x74, 0xb8, 0xc7, 0x93, 0x85, 0x67, 0x5b,
        0xae, 0x93, 0x7b, 0x02, 0x03, 0x01, 0x00, 0x01,
        0x02, 0x81, 0x80, 0x31, 0x4c, 0xd5, 0x6a, 0x48,
        0x01, 0xf0, 0x51, 0x47, 0x2b, 0xe8, 0x9b, 0xad,
        0x32, 0x5e, 0x2f, 0x5b, 0x6f, 0x2b, 0xa5, 0xf3,
        0x03, 0x86, 0xb9, 0x20, 0x9b, 0x47, 0x9f, 0xaa,
        0xc4, 0xc2, 0xa6, 0x28, 0x2c, 0xf3, 0x2e, 0xd5,
        0x9a, 0x91, 0x1d, 0x55, 0x26, 0x82, 0xd4, 0xa0,
        0x20, 0x2b, 0xc8, 0xa0, 0x3e, 0x8d, 0x21, 0xf7,
        0xed, 0x3b, 0x3f, 0x23, 0x36, 0x13, 0xab, 0x39,
        0x4f, 0xb8, 0xe3, 0xde, 0x5b, 0xe3, 0x3b, 0xaf,
        0xd3, 0xf1, 0xae, 0xbc, 0x52, 0x2b, 0x40, 0xc8,
        0xac, 0xe5, 0x76, 0xcc, 0xe9, 0x39, 0x2a, 0x7a,
        0xb2, 0xf2, 0xb1, 0x6a, 0xe7, 0x96, 0x51, 0x9a,
        0x34, 0x8e, 0x03, 0x4b, 0x7f, 0x36, 0x24, 0x8f,
        0xf0, 0x99, 0xa2, 0x50, 0xb4, 0xf4, 0xc1, 0x86,
        0xe1, 0x53, 0xcf, 0xcc, 0xaa, 0xf3, 0xce, 0x5a,
        0x38, 0xc5, 0xd9, 0x31, 0xd5, 0x3f, 0x27, 0x14,
        0x3b, 0xe3, 0x19, 0x02, 0x41, 0x00, 0xc9, 0x8e,
        0xc7, 0xb6, 0x18, 0x62, 0x4d, 0x2a, 0x14, 0xd5,
        0x20, 0x8e, 0xd9, 0x5a, 0x9a, 0x6b, 0xed, 0x98,
        0x1f, 0x06, 0x5e, 0x36, 0xe6, 0xaf, 0xb7, 0x0e,
        0x3e, 0x78, 0xb2, 0x13, 0x4b, 0x87, 0xc5, 0x18,
        0xf9, 0x89, 0x1a, 0x3f, 0xc0, 0x8e, 0x03, 0x2a,
        0xe7, 0x28, 0xf0, 0x5e, 0xa3, 0x28, 0x1d, 0x68,
        0xc6, 0xe6, 0xf7, 0x62, 0x95, 0x20, 0x52, 0xa8,
        0xc7, 0xde, 0xe2, 0x83, 0x09, 0x5f, 0x02, 0x41,
        0x00, 0xc3, 0xe3, 0xca, 0x44, 0xfe, 0x7a, 0x0d,
        0x6c, 0x66, 0x16, 0xe4, 0x86, 0x93, 0x9b, 0xe3,
        0x36, 0x27, 0xa2, 0xfe, 0x07, 0x5f, 0x67, 0xe0,
        0xb0, 0x42, 0x0a, 0xe3, 0x0a, 0xb1, 0x26, 0xd4,
        0x3c, 0xbe, 0xf6, 0x67, 0xbe, 0xf2, 0xa0, 0x58,
        0xeb, 0x80, 0x2e, 0x90, 0x4a, 0x7d, 0x47, 0x70,
        0x31, 0xe2, 0x88, 0x5b, 0xc2, 0x16, 0xfb, 0xc4,
        0x3c, 0x29, 0x6a, 0x5b, 0x08, 0xe0, 0xc2, 0xbf,
        0x65, 0x02, 0x40, 0x3c, 0x81, 0x00, 0xd0, 0x57,
        0xc7, 0x82, 0x74, 0x64, 0x66, 0x89, 0xec, 0x77,
        0xb0, 0xab, 0xf4, 0x44, 0x11, 0x4b, 0x16, 0xe5,
        0x47, 0x43, 0xbe, 0x71, 0x8b, 0xf4, 0x12, 0xd5,
        0x19, 0xd7, 0xad, 0x7c, 0xeb, 0xff, 0x54, 0x39,
        0xad, 0xf3, 0x86, 0x6d, 0xca, 0xfe, 0x33, 0x1a,
        0xdc, 0xbd, 0xcb, 0x77, 0xf0, 0x90, 0xec, 0x9a,
        0x4c, 0x5c, 0x89, 0xa4, 0x66, 0x88, 0x01, 0x0f,
        0x2b, 0xd8, 0xaf, 0x02, 0x41, 0x00, 0xaf, 0xd0,
        0x0e, 0x86, 0x85, 0xef, 0x7d, 0x84, 0xc0, 0xcb,
        0xe3, 0x27, 0x75, 0xeb, 0xff, 0xad, 0x67, 0x3d,
        0xbe, 0xc9, 0x57, 0x33, 0xa0, 0x52, 0x11, 0xb4,
        0x3b, 0xba, 0x28, 0xed, 0x34, 0xa7, 0xa0, 0xac,
        0xfe, 0xc8, 0x3e, 0x72, 0xf3, 0xdb, 0xca, 0x1c,
        0x00, 0x9d, 0x1a, 0x7b, 0xb7, 0x92, 0xce, 0x42,
        0x9c, 0x38, 0x42, 0xf0, 0x8c, 0x5b, 0x82, 0xc0,
        0x56, 0x1c, 0x4d, 0xbd, 0xfc, 0x91, 0x02, 0x40,
        0x02, 0x0b, 0x0a, 0x74, 0xbf, 0xc3, 0x89, 0xfa,
        0xcf, 0x0d, 0x5d, 0xed, 0xb4, 0x9a, 0xf4, 0xeb,
        0xda, 0xef, 0xd4, 0x9d, 0xd4, 0xc8, 0xf3, 0xc2,
        0x65, 0x25, 0x92, 0x62, 0xd2, 0x1f, 0xed, 0x09,
        0x47, 0xda, 0x43, 0x69, 0xd4, 0x2a, 0xf6, 0x3f,
        0x32, 0x52, 0x99, 0xe0, 0x4a, 0xb8, 0x37, 0x83,
        0xbd, 0xd3, 0xf6, 0x4e, 0x7c, 0x11, 0x19, 0xec,
        0xbe, 0xc8, 0x7e, 0xc2, 0xa2, 0x7e, 0xf3, 0x22,
};

static const char x509_public_certificate_rsa2048_der[] = {
        0x30, 0x82, 0x04, 0x0d, 0x30, 0x82, 0x02, 0xf5, 
        0xa0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x14, 0x18, 
        0xfd, 0x79, 0x34, 0x35, 0xc3, 0xd4, 0x63, 0x89, 
        0xf5, 0xe8, 0xab, 0x24, 0x8f, 0xef, 0x15, 0x9e, 
        0x0e, 0x9c, 0x8e, 0x30, 0x0d, 0x06, 0x09, 0x2a, 
        0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0b, 
        0x05, 0x00, 0x30, 0x81, 0x95, 0x31, 0x0b, 0x30, 
        0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 
        0x46, 0x52, 0x31, 0x13, 0x30, 0x11, 0x06, 0x03, 
        0x55, 0x04, 0x08, 0x0c, 0x0a, 0x53, 0x6f, 0x6d, 
        0x65, 0x2d, 0x53, 0x74, 0x61, 0x74, 0x65, 0x31, 
        0x12, 0x30, 0x10, 0x06, 0x03, 0x55, 0x04, 0x07, 
        0x0c, 0x09, 0x4b, 0x6f, 0x67, 0x65, 0x6e, 0x68, 
        0x65, 0x69, 0x6d, 0x31, 0x21, 0x30, 0x1f, 0x06, 
        0x03, 0x55, 0x04, 0x0a, 0x0c, 0x18, 0x49, 0x6e, 
        0x74, 0x65, 0x72, 0x6e, 0x65, 0x74, 0x20, 0x57, 
        0x69, 0x64, 0x67, 0x69, 0x74, 0x73, 0x20, 0x50, 
        0x74, 0x79, 0x20, 0x4c, 0x74, 0x64, 0x31, 0x17, 
        0x30, 0x15, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0c, 
        0x0e, 0x4c, 0x75, 0x63, 0x61, 0x73, 0x20, 0x44, 
        0x69, 0x65, 0x74, 0x72, 0x69, 0x63, 0x68, 0x31, 
        0x21, 0x30, 0x1f, 0x06, 0x09, 0x2a, 0x86, 0x48, 
        0x86, 0xf7, 0x0d, 0x01, 0x09, 0x01, 0x16, 0x12, 
        0x6c, 0x64, 0x2e, 0x61, 0x64, 0x65, 0x63, 0x79, 
        0x40, 0x67, 0x6d, 0x61, 0x69, 0x6c, 0x2e, 0x63, 
        0x6f, 0x6d, 0x30, 0x1e, 0x17, 0x0d, 0x32, 0x31, 
        0x31, 0x31, 0x31, 0x35, 0x32, 0x31, 0x30, 0x37, 
        0x33, 0x31, 0x5a, 0x17, 0x0d, 0x32, 0x32, 0x31, 
        0x31, 0x31, 0x35, 0x32, 0x31, 0x30, 0x37, 0x33, 
        0x31, 0x5a, 0x30, 0x81, 0x95, 0x31, 0x0b, 0x30, 
        0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 
        0x46, 0x52, 0x31, 0x13, 0x30, 0x11, 0x06, 0x03,
        0x55, 0x04, 0x08, 0x0c, 0x0a, 0x53, 0x6f, 0x6d,
        0x65, 0x2d, 0x53, 0x74, 0x61, 0x74, 0x65, 0x31,
        0x12, 0x30, 0x10, 0x06, 0x03, 0x55, 0x04, 0x07,
        0x0c, 0x09, 0x4b, 0x6f, 0x67, 0x65, 0x6e, 0x68,
        0x65, 0x69, 0x6d, 0x31, 0x21, 0x30, 0x1f, 0x06,
        0x03, 0x55, 0x04, 0x0a, 0x0c, 0x18, 0x49, 0x6e,
        0x74, 0x65, 0x72, 0x6e, 0x65, 0x74, 0x20, 0x57,
        0x69, 0x64, 0x67, 0x69, 0x74, 0x73, 0x20, 0x50,
        0x74, 0x79, 0x20, 0x4c, 0x74, 0x64, 0x31, 0x17,
        0x30, 0x15, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0c,
        0x0e, 0x4c, 0x75, 0x63, 0x61, 0x73, 0x20, 0x44,
        0x69, 0x65, 0x74, 0x72, 0x69, 0x63, 0x68, 0x31,
        0x21, 0x30, 0x1f, 0x06, 0x09, 0x2a, 0x86, 0x48,
        0x86, 0xf7, 0x0d, 0x01, 0x09, 0x01, 0x16, 0x12,
        0x6c, 0x64, 0x2e, 0x61, 0x64, 0x65, 0x63, 0x79,
        0x40, 0x67, 0x6d, 0x61, 0x69, 0x6c, 0x2e, 0x63,
        0x6f, 0x6d, 0x30, 0x82, 0x01, 0x22, 0x30, 0x0d,
        0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d,
        0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x82, 0x01,
        0x0f, 0x00, 0x30, 0x82, 0x01, 0x0a, 0x02, 0x82,
        0x01, 0x01, 0x00, 0xc9, 0x5d, 0x1e, 0xee, 0xbc,
        0x53, 0x84, 0x04, 0xd3, 0xbc, 0x1a, 0x9b, 0xf9,
        0x65, 0x1d, 0x80, 0xab, 0x69, 0x06, 0x09, 0xd4,
        0x21, 0xe6, 0x93, 0x1b, 0x8e, 0xa8, 0xa7, 0xf0,
        0xc5, 0x0a, 0x74, 0x0d, 0xdb, 0xb2, 0x16, 0x64,
        0xd1, 0xf0, 0xae, 0x59, 0x56, 0xc7, 0x3a, 0xe6,
        0xb0, 0x96, 0x71, 0x06, 0x14, 0x0c, 0xa1, 0x6e,
        0xc3, 0x84, 0x6e, 0x95, 0x1a, 0xb4, 0xff, 0xbd,
        0xfa, 0xc2, 0x66, 0xe2, 0x6b, 0x9a, 0x9e, 0x5a,
        0xb3, 0x4d, 0x64, 0xe2, 0x66, 0xfd, 0xaf, 0x40,
        0xe3, 0xd3, 0xfa, 0x5a, 0x3d, 0x96, 0x0d, 0xb7,
        0x4c, 0xeb, 0xe1, 0x26, 0xc9, 0x97, 0x50, 0x7f,
        0x1c, 0x5f, 0xb3, 0x18, 0xec, 0x43, 0x54, 0x82,
        0xaa, 0x46, 0xac, 0x02, 0x62, 0x03, 0x80, 0x36,
        0x91, 0x5b, 0xfc, 0x57, 0xdc, 0x65, 0x93, 0xe1,
        0xee, 0x81, 0x15, 0x32, 0xde, 0x9a, 0x19, 0xc8,
        0x16, 0x7e, 0x03, 0xbe, 0x29, 0xcf, 0x52, 0xc8,
        0x3f, 0xc9, 0xd5, 0x69, 0xab, 0x40, 0xa1, 0xe2,
        0x3a, 0x2f, 0x79, 0x79, 0x3f, 0xc5, 0x80, 0xed,
        0xe3, 0xa6, 0x20, 0x85, 0xed, 0x2d, 0xa9, 0xad,
        0xaf, 0x95, 0xbd, 0x5b, 0xcb, 0xcb, 0x90, 0x74,
        0x49, 0xa6, 0xaf, 0x65, 0x28, 0xf3, 0x5e, 0xbd,
        0xea, 0x45, 0x6b, 0x0b, 0x0a, 0xcf, 0x33, 0xa7,
        0x43, 0xf9, 0xde, 0xe1, 0xe2, 0x8a, 0x3c, 0x9e,
        0x00, 0x60, 0x4b, 0xdd, 0xeb, 0x6d, 0x1f, 0x9c,
        0x9d, 0xd3, 0x21, 0x20, 0xa7, 0x6c, 0x61, 0xd6,
        0x1c, 0x5a, 0xfa, 0xe7, 0x9d, 0x82, 0xeb, 0x38,
        0x32, 0x94, 0x33, 0xff, 0x04, 0xd4, 0x20, 0x2b,
        0x18, 0xd7, 0x3d, 0x2c, 0x33, 0x14, 0xb6, 0x7c,
        0x1d, 0x98, 0x56, 0x24, 0x71, 0xfd, 0xf6, 0x79,
        0x7f, 0xda, 0x5a, 0xc6, 0x28, 0xca, 0x78, 0xd5,
        0x78, 0xf9, 0x08, 0x63, 0xac, 0x27, 0x25, 0xf3,
        0x19, 0x2b, 0xf3, 0x02, 0x03, 0x01, 0x00, 0x01,
        0xa3, 0x53, 0x30, 0x51, 0x30, 0x1d, 0x06, 0x03,
        0x55, 0x1d, 0x0e, 0x04, 0x16, 0x04, 0x14, 0xa6,
        0x89, 0x7b, 0x56, 0xfd, 0xf5, 0x33, 0x1b, 0x0e,
        0xb2, 0xee, 0x97, 0x42, 0x59, 0xfa, 0xb8, 0xc4,
        0x4b, 0xbb, 0xcf, 0x30, 0x1f, 0x06, 0x03, 0x55,
        0x1d, 0x23, 0x04, 0x18, 0x30, 0x16, 0x80, 0x14,
        0xa6, 0x89, 0x7b, 0x56, 0xfd, 0xf5, 0x33, 0x1b,
        0x0e, 0xb2, 0xee, 0x97, 0x42, 0x59, 0xfa, 0xb8,
        0xc4, 0x4b, 0xbb, 0xcf, 0x30, 0x0f, 0x06, 0x03,
        0x55, 0x1d, 0x13, 0x01, 0x01, 0xff, 0x04, 0x05,
        0x30, 0x03, 0x01, 0x01, 0xff, 0x30, 0x0d, 0x06,
        0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01,
        0x01, 0x0b, 0x05, 0x00, 0x03, 0x82, 0x01, 0x01,
        0x00, 0xc0, 0xdd, 0x0a, 0x24, 0xd0, 0x61, 0x27,
        0x8d, 0xde, 0x68, 0x03, 0xf3, 0x0e, 0x0b, 0xb4,
        0x6d, 0xf1, 0x3b, 0xca, 0x03, 0x77, 0x2e, 0xae,
        0x42, 0x34, 0xb9, 0x9d, 0x8d, 0x99, 0x28, 0xd8,
        0xf0, 0x73, 0x54, 0xd3, 0xd1, 0xa8, 0x33, 0x75,
        0xa0, 0x39, 0xd5, 0x3b, 0xc1, 0x41, 0x01, 0x7d,
        0xfc, 0xfa, 0xda, 0x69, 0x47, 0x99, 0xdf, 0x3c,
        0x63, 0xb9, 0x71, 0x00, 0x08, 0x37, 0xde, 0x0e,
        0x5b, 0xc6, 0xeb, 0xcb, 0xa3, 0x2e, 0x81, 0xdf,
        0xa0, 0x6e, 0x95, 0x04, 0x5d, 0x8d, 0xf7, 0x7d,
        0x04, 0x66, 0xc9, 0x9c, 0x93, 0x6d, 0x5c, 0xd0,
        0x30, 0xbb, 0x3c, 0x32, 0xbd, 0x44, 0xe7, 0xd1,
        0xcf, 0x43, 0xbb, 0x6d, 0x88, 0x44, 0xe7, 0x62,
        0xe6, 0x43, 0x25, 0xd2, 0xfc, 0xde, 0x97, 0x8c,
        0xf0, 0xb0, 0x1a, 0xae, 0xe8, 0x84, 0x97, 0x43,
        0xc1, 0xd4, 0x6d, 0x41, 0xab, 0x9b, 0x53, 0x7a,
        0x92, 0x64, 0x2f, 0x5a, 0xd2, 0xc9, 0x1e, 0xe0,
        0x9a, 0xfc, 0xbd, 0x9b, 0xb5, 0x79, 0x91, 0x94,
        0xcf, 0x10, 0x18, 0xfd, 0x8b, 0x55, 0x80, 0x69,
        0xaa, 0x1b, 0x84, 0x64, 0xb3, 0x40, 0x06, 0x1a,
        0xc3, 0x76, 0xfc, 0xf4, 0x34, 0x9a, 0xff, 0x22,
        0xdc, 0x2b, 0xed, 0xbd, 0x9e, 0x67, 0x93, 0xce,
        0xd2, 0x6c, 0x05, 0x45, 0x42, 0xd9, 0x8c, 0xd0,
        0x70, 0x66, 0x2a, 0x21, 0x13, 0xa1, 0x6f, 0xdb,
        0x0f, 0x56, 0x10, 0xcd, 0x66, 0x1e, 0x13, 0x75,
        0x66, 0xd1, 0x89, 0xad, 0xa7, 0xaa, 0x06, 0xbd,
        0xb9, 0xe3, 0x27, 0xdc, 0x93, 0x8b, 0xf5, 0x6a,
        0x42, 0xff, 0xcd, 0x3a, 0x90, 0x24, 0xae, 0x8c,
        0xd4, 0x66, 0x69, 0xf2, 0xfd, 0xf0, 0x62, 0x19,
        0x6a, 0x7d, 0xaf, 0xe0, 0x5e, 0xc7, 0x20, 0xba,
        0xdc, 0x49, 0x73, 0x4d, 0x23, 0x0c, 0x71, 0x75,
        0x40, 0x6d, 0xe9, 0xd5, 0x16, 0xbe, 0x13, 0x44,
        0x76, };
        
static const char rsa_private_key_rsa2048_der[] = {
        0x30, 0x82, 0x04, 0xa3, 0x02, 0x01, 0x00, 0x02,
        0x82, 0x01, 0x01, 0x00, 0xc9, 0x5d, 0x1e, 0xee,
        0xbc, 0x53, 0x84, 0x04, 0xd3, 0xbc, 0x1a, 0x9b,
        0xf9, 0x65, 0x1d, 0x80, 0xab, 0x69, 0x06, 0x09,
        0xd4, 0x21, 0xe6, 0x93, 0x1b, 0x8e, 0xa8, 0xa7,
        0xf0, 0xc5, 0x0a, 0x74, 0x0d, 0xdb, 0xb2, 0x16,
        0x64, 0xd1, 0xf0, 0xae, 0x59, 0x56, 0xc7, 0x3a,
        0xe6, 0xb0, 0x96, 0x71, 0x06, 0x14, 0x0c, 0xa1,
        0x6e, 0xc3, 0x84, 0x6e, 0x95, 0x1a, 0xb4, 0xff,
        0xbd, 0xfa, 0xc2, 0x66, 0xe2, 0x6b, 0x9a, 0x9e,
        0x5a, 0xb3, 0x4d, 0x64, 0xe2, 0x66, 0xfd, 0xaf,
        0x40, 0xe3, 0xd3, 0xfa, 0x5a, 0x3d, 0x96, 0x0d,
        0xb7, 0x4c, 0xeb, 0xe1, 0x26, 0xc9, 0x97, 0x50,
        0x7f, 0x1c, 0x5f, 0xb3, 0x18, 0xec, 0x43, 0x54,
        0x82, 0xaa, 0x46, 0xac, 0x02, 0x62, 0x03, 0x80,
        0x36, 0x91, 0x5b, 0xfc, 0x57, 0xdc, 0x65, 0x93,
        0xe1, 0xee, 0x81, 0x15, 0x32, 0xde, 0x9a, 0x19,
        0xc8, 0x16, 0x7e, 0x03, 0xbe, 0x29, 0xcf, 0x52,
        0xc8, 0x3f, 0xc9, 0xd5, 0x69, 0xab, 0x40, 0xa1,
        0xe2, 0x3a, 0x2f, 0x79, 0x79, 0x3f, 0xc5, 0x80,
        0xed, 0xe3, 0xa6, 0x20, 0x85, 0xed, 0x2d, 0xa9,
        0xad, 0xaf, 0x95, 0xbd, 0x5b, 0xcb, 0xcb, 0x90,
        0x74, 0x49, 0xa6, 0xaf, 0x65, 0x28, 0xf3, 0x5e,
        0xbd, 0xea, 0x45, 0x6b, 0x0b, 0x0a, 0xcf, 0x33,
        0xa7, 0x43, 0xf9, 0xde, 0xe1, 0xe2, 0x8a, 0x3c,
        0x9e, 0x00, 0x60, 0x4b, 0xdd, 0xeb, 0x6d, 0x1f,
        0x9c, 0x9d, 0xd3, 0x21, 0x20, 0xa7, 0x6c, 0x61,
        0xd6, 0x1c, 0x5a, 0xfa, 0xe7, 0x9d, 0x82, 0xeb,
        0x38, 0x32, 0x94, 0x33, 0xff, 0x04, 0xd4, 0x20,
        0x2b, 0x18, 0xd7, 0x3d, 0x2c, 0x33, 0x14, 0xb6,
        0x7c, 0x1d, 0x98, 0x56, 0x24, 0x71, 0xfd, 0xf6,
        0x79, 0x7f, 0xda, 0x5a, 0xc6, 0x28, 0xca, 0x78,
        0xd5, 0x78, 0xf9, 0x08, 0x63, 0xac, 0x27, 0x25,
        0xf3, 0x19, 0x2b, 0xf3, 0x02, 0x03, 0x01, 0x00,
        0x01, 0x02, 0x82, 0x01, 0x00, 0x37, 0x4c, 0x99,
        0x88, 0x1a, 0xb4, 0x1c, 0xd7, 0x6e, 0x86, 0x84,
        0x10, 0x3d, 0xa7, 0x65, 0x38, 0xc6, 0xda, 0x2a,
        0xcc, 0x5c, 0x33, 0x8b, 0x2c, 0xef, 0x2e, 0x78,
        0x66, 0xd6, 0x9a, 0x66, 0x4a, 0x84, 0xdb, 0xc6,
        0xc6, 0x9b, 0x9d, 0x84, 0x29, 0x7d, 0x63, 0x75,
        0x87, 0x59, 0x7f, 0x39, 0x71, 0x84, 0xa7, 0xd0,
        0xe8, 0x2c, 0x91, 0x09, 0x37, 0x8d, 0x3f, 0x2e,
        0x61, 0xe5, 0x7c, 0x8e, 0x12, 0xcf, 0x2f, 0x99,
        0xe0, 0xcf, 0x2b, 0xda, 0x9f, 0x50, 0x05, 0xd4,
        0xb9, 0x62, 0x6a, 0xae, 0xf6, 0x5b, 0xfd, 0xf9,
        0xcd, 0x7e, 0x7f, 0x63, 0x70, 0x0b, 0xc4, 0xe5,
        0x07, 0x38, 0x41, 0x44, 0x8e, 0xdc, 0xd3, 0x55,
        0x92, 0x49, 0xe8, 0x15, 0x4c, 0x7b, 0xc3, 0x0b,
        0x0f, 0x14, 0xed, 0x4a, 0x83, 0xbc, 0x65, 0x4c,
        0x88, 0x16, 0x4d, 0xf7, 0xa9, 0x28, 0xb5, 0x35,
        0x40, 0xcb, 0x50, 0x51, 0xfe, 0x9c, 0x35, 0x53,
        0xce, 0xa4, 0xb7, 0xaa, 0x81, 0xdf, 0x51, 0x19,
        0xee, 0x04, 0x34, 0xd9, 0x50, 0xe5, 0xe5, 0xa0,
        0x02, 0x9d, 0xa1, 0xf6, 0x30, 0x44, 0x29, 0x38,
        0xfd, 0x65, 0x46, 0x2b, 0x47, 0x56, 0x5d, 0xd9,
        0x58, 0x27, 0x3d, 0x50, 0x19, 0x99, 0xbe, 0xdf,
        0x41, 0xf2, 0xe6, 0x71, 0x23, 0xc1, 0x4b, 0xdd,
        0x13, 0x1a, 0xa5, 0x41, 0x36, 0x67, 0xaa, 0xf8,
        0xbc, 0x85, 0xb0, 0x25, 0x10, 0x2b, 0xa7, 0x47,
        0x56, 0x19, 0x01, 0x1b, 0x7e, 0x90, 0x75, 0xb6,
        0xd8, 0x6b, 0x58, 0xd4, 0xce, 0xb1, 0xed, 0x9b,
        0xfa, 0x3a, 0xb7, 0x6d, 0xf2, 0x8b, 0x79, 0x80,
        0x22, 0xea, 0x78, 0xb2, 0x50, 0x35, 0x3a, 0xc6,
        0xb2, 0xd0, 0x23, 0x25, 0xc8, 0xa1, 0x0d, 0xfb,
        0x4b, 0x58, 0xf8, 0x42, 0x87, 0xc8, 0xcb, 0xf8,
        0x37, 0xf3, 0x78, 0x6b, 0xf5, 0x70, 0x03, 0xe4,
        0x6e, 0x45, 0x9e, 0x9c, 0x21, 0x02, 0x81, 0x81,
        0x00, 0xf1, 0x42, 0x25, 0x2c, 0x1f, 0xb2, 0xfd,
        0xa4, 0xf9, 0x24, 0x35, 0xc7, 0x90, 0xcd, 0xcb,
        0xa6, 0x65, 0x91, 0x26, 0xc2, 0x8d, 0xea, 0x2b,
        0xfc, 0x76, 0x04, 0x89, 0x72, 0xa6, 0x01, 0x53,
        0xaa, 0x2a, 0x8f, 0x1f, 0xbe, 0x03, 0x49, 0x16,
        0x32, 0xa3, 0xce, 0x43, 0x35, 0x4e, 0xe9, 0x8f,
        0xae, 0x38, 0x7e, 0x07, 0x93, 0x33, 0x03, 0xc0,
        0x25, 0x59, 0x74, 0x42, 0x3e, 0xe1, 0x78, 0x0a,
        0xa2, 0x42, 0x88, 0xa2, 0xc4, 0x55, 0x31, 0x02,
        0xa7, 0xab, 0xdf, 0x37, 0x2d, 0xdd, 0x03, 0x0e,
        0x1f, 0x64, 0xc5, 0xc9, 0x2a, 0x4d, 0xa2, 0x99,
        0xb2, 0x90, 0x99, 0x6f, 0xad, 0x9b, 0x9e, 0x2b,
        0x9e, 0x56, 0x67, 0x2d, 0x7b, 0x6e, 0x02, 0x6b,
        0x81, 0xf1, 0x7e, 0xff, 0xd2, 0xd6, 0xbf, 0x5a,
        0x39, 0xf0, 0x52, 0x36, 0x45, 0x60, 0x2b, 0x3f,
        0xb0, 0xfd, 0xe7, 0x49, 0x31, 0x06, 0xc8, 0xa5,
        0xab, 0x02, 0x81, 0x81, 0x00, 0xd5, 0xaa, 0xed,
        0xc5, 0x79, 0x52, 0x93, 0x8e, 0x7d, 0x66, 0x82,
        0x51, 0x1d, 0x02, 0xb6, 0xc0, 0xbd, 0x47, 0x7f,
        0xb4, 0x32, 0x1b, 0xd8, 0x28, 0x2e, 0x9c, 0x69,
        0xf9, 0x52, 0xc9, 0xdf, 0x74, 0x42, 0xb7, 0x24,
        0x69, 0x51, 0xb7, 0xa9, 0x9f, 0x3c, 0x69, 0x70,
        0x2b, 0xe8, 0x03, 0x69, 0x70, 0x34, 0xf4, 0xa3,
        0x00, 0x3d, 0xbd, 0x7b, 0x78, 0xd4, 0x9f, 0x51,
        0xb2, 0xf1, 0x10, 0xd8, 0x0f, 0xd6, 0x64, 0xe1,
        0xa9, 0xfd, 0x1a, 0x4f, 0x28, 0x02, 0xe6, 0xff,
        0x7d, 0xf6, 0x68, 0x2e, 0xe8, 0xac, 0x00, 0x85,
        0x53, 0xb2, 0x2f, 0x22, 0x29, 0x73, 0x7b, 0x87,
        0x17, 0x3c, 0x29, 0x62, 0x69, 0x72, 0x0b, 0x91,
        0xec, 0x12, 0x99, 0xf7, 0x9b, 0x4a, 0xb9, 0x02,
        0xf4, 0xd5, 0xef, 0x4d, 0xcd, 0xc7, 0x22, 0x60,
        0x99, 0x22, 0x66, 0xe8, 0x82, 0x70, 0x6a, 0xfe,
        0xa4, 0x04, 0x74, 0x3a, 0xd9, 0x02, 0x81, 0x80,
        0x6f, 0x97, 0x01, 0xac, 0x94, 0x08, 0xed, 0x4b,
        0x26, 0x35, 0xba, 0x6e, 0x51, 0x2a, 0xef, 0x1c,
        0x4a, 0xf4, 0x45, 0x72, 0x4d, 0xc3, 0xd7, 0x8e,
        0x91, 0x63, 0xed, 0xd3, 0x4a, 0xb7, 0x68, 0x64,
        0x58, 0x05, 0x15, 0x50, 0x85, 0x22, 0x84, 0x12,
        0xee, 0x33, 0x54, 0x60, 0xce, 0xdc, 0x37, 0x2a,
        0x05, 0x55, 0x3d, 0xd9, 0xb7, 0x09, 0xf0, 0x11,
        0x16, 0x7c, 0x30, 0xbb, 0xf6, 0xfb, 0xd8, 0x27,
        0x4f, 0x10, 0xf6, 0x00, 0x4b, 0xcb, 0x3c, 0x88,
        0x23, 0x76, 0x3e, 0x86, 0x87, 0x28, 0x87, 0x9a,
        0xbb, 0xb8, 0xc4, 0x20, 0x3e, 0x02, 0x8c, 0x86,
        0xcc, 0x5d, 0x3c, 0x0b, 0x97, 0xe4, 0x24, 0x16,
        0xbb, 0xae, 0x43, 0x9a, 0x48, 0xba, 0xf3, 0xd1,
        0x09, 0xcb, 0x8d, 0x36, 0x8f, 0x3f, 0xb8, 0xd2,
        0xfd, 0xb6, 0x79, 0x05, 0xc3, 0xc2, 0x9d, 0x56,
        0x17, 0x4a, 0xa8, 0x4e, 0xf5, 0xed, 0x4e, 0xbb,
        0x02, 0x81, 0x81, 0x00, 0xce, 0x35, 0x4d, 0x8e,
        0x04, 0x9d, 0xb6, 0x3c, 0x91, 0x37, 0xaa, 0x53,
        0x40, 0x0d, 0x4b, 0x74, 0xcd, 0xf7, 0xbf, 0xfe,
        0x97, 0x51, 0x9a, 0x16, 0x85, 0x8d, 0x7d, 0x15,
        0x1b, 0x5a, 0x2a, 0xa6, 0xd8, 0x70, 0x49, 0xda,
        0xbe, 0xfb, 0xe2, 0xdf, 0x03, 0xfd, 0xba, 0x3d,
        0x15, 0x88, 0x9d, 0x6c, 0xa6, 0x1e, 0xe7, 0x65,
        0x27, 0x30, 0xc4, 0x86, 0x03, 0xa5, 0xd2, 0xc2,
        0x40, 0xb7, 0x01, 0xde, 0x9f, 0x09, 0xf3, 0x64,
        0x0c, 0x1a, 0x25, 0x04, 0xb7, 0x70, 0x5a, 0x69,
        0x25, 0xb2, 0xbc, 0x7a, 0xde, 0xed, 0x0d, 0xbf,
        0x8d, 0xba, 0xc1, 0x5c, 0x81, 0xd0, 0x58, 0xbb,
        0x0a, 0xdb, 0xe1, 0xd7, 0x64, 0x32, 0x58, 0x5d,
        0x1e, 0x42, 0xab, 0xdd, 0x9a, 0x8a, 0xdd, 0x98,
        0x8f, 0x13, 0x89, 0xe2, 0x2b, 0xea, 0x38, 0x91,
        0xf1, 0xca, 0xa1, 0x60, 0xa9, 0xc0, 0x09, 0x0b,
        0x20, 0x25, 0x50, 0x59, 0x02, 0x81, 0x80, 0x30,
        0x92, 0x5a, 0xbb, 0x45, 0xb5, 0xd1, 0x45, 0x33,
        0x22, 0x16, 0xd9, 0x9c, 0xcf, 0x63, 0x50, 0x2e,
        0x44, 0xaf, 0x24, 0x16, 0x1f, 0x8e, 0x95, 0x42,
        0x6e, 0x6f, 0x9e, 0x27, 0x99, 0x5c, 0x91, 0x16,
        0xf9, 0xf0, 0xfa, 0x51, 0xc4, 0x0d, 0x13, 0x88,
        0x47, 0x9f, 0xf1, 0x6c, 0x80, 0x25, 0x3a, 0x5f,
        0x91, 0x0b, 0x1c, 0xea, 0xe9, 0x72, 0xcf, 0xad,
        0xc5, 0xd6, 0x54, 0xb5, 0x59, 0x56, 0xeb, 0x12,
        0x5f, 0xca, 0xad, 0x57, 0xb0, 0x0e, 0xfb, 0x00,
        0x55, 0x54, 0xe8, 0xaa, 0xba, 0xd0, 0xe0, 0xc6,
        0xba, 0xce, 0xf6, 0x83, 0x2e, 0xe6, 0xce, 0xaf,
        0x24, 0x3e, 0xde, 0xa8, 0xa3, 0x01, 0x1a, 0x80,
        0xca, 0xe5, 0xf9, 0x73, 0xcb, 0x32, 0xba, 0x71,
        0x33, 0xab, 0xc4, 0xc5, 0x22, 0x67, 0xb9, 0xd6,
        0x0e, 0xff, 0xb8, 0xd0, 0xef, 0x60, 0xf1, 0x94,
        0x5b, 0x0c, 0xe4, 0xe8, 0xe7, 0x79, 0x6f, };

#endif /* _HTTP_CREDENTIAL_H_ */