#include <stdio.h>

/*
 * Game Genie: Code Mapping
 *
 * 6 Letters:
 * |  1 |  2 |  3 |  4 |  5 |  6 |
 * |1678|H234|#IJK|LABC|DMNO|5EFG|
 * Value bits:   12345678
 * Address bits: ABCDEFGHJKLMNO
 * Length bit:   # <- determines if 6 (0) or 8 (1) letters
 *
 * 8 Letters:
 * |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |
 * |1678|H234|#IJK|LABC|DMNO|εEFG|αζηθ|5βγδ|
 * Value bits:   12345678
 * Address bits: ABCDEFGHJKLMNO
 * Compare bits: αβγδεζηθ
 * Length bit:   # <- determines if 6 (0) or 8 (1) letters
*/

// Letters: Group 1
#define A 0x0 // 0000
#define P 0x1 // 0001
#define Z 0x2 // 0010
#define L 0x3 // 0011
#define G 0x4 // 0100
#define I 0x5 // 0101
#define T 0x6 // 0110
#define Y 0x7 // 0111
// Letters: Group 2
#define E 0x8 // 1000
#define O 0x9 // 1001
#define X 0xA // 1010
#define U 0xB // 1011
#define K 0xC // 1100
#define S 0xD // 1101
#define V 0xE // 1110
#define N 0xF // 1111

#define ADDR_LEN 15
#define VAL_LEN  8
#define CMP_LEN  8
#define CONVERSION_SUCCESS  0
#define ERROR_INVALID_LEN  -1
#define ERROR_INVALID_CHAR -2

typedef unsigned int   uint;
typedef unsigned short ushort;

ushort convertLetter(char letter) {
    switch (letter) {
        case 'A':
        case 'a':
            return A;
            break;
        
        case 'P':
        case 'p':
            return P;
            break;
        
        case 'Z':
        case 'z':
            return Z;
            break;
        
        case 'L':
        case 'l':
            return L;
            break;
        
        case 'G':
        case 'g':
            return G;
            break;
        
        case 'I':
        case 'i':
            return I;
            break;
        
        case 'T':
        case 't':
            return T;
            break;
        
        case 'Y':
        case 'y':
            return Y;
            break;
        
        case 'E':
        case 'e':
            return E;
            break;
        
        case 'O':
        case 'o':
            return O;
            break;
        
        case 'X':
        case 'x':
            return X;
            break;
        
        case 'U':
        case 'u':
            return U;
            break;
        
        case 'K':
        case 'k':
            return K;
            break;
        
        case 'S':
        case 's':
            return S;
            break;
        
        case 'V':
        case 'v':
            return V;
            break;
        
        case 'N':
        case 'n':
            return N;
            break;
        
        default:
            return ERROR_INVALID_CHAR;
    }
}

struct Code {
    ushort addr;
    ushort val;
    ushort cmp;
    ushort len;
};

#define LENGTH6 ADDR_LEN + VAL_LEN + 1
#define LENGTH8 ADDR_LEN + VAL_LEN + CMP_LEN + 1
int decode(char * codeIn, uint length, struct Code * codeOut) {
    if (length != 6 && length != 8) {
        printf("ERROR: Length %d is invalid\n", length);
        return ERROR_INVALID_LEN;
    }
    
    ushort len = 0;
    ushort addr[ADDR_LEN];
    ushort val[VAL_LEN];
    ushort cmp[CMP_LEN];
    
    ushort * maps6[LENGTH6] = {
        val  + 0,  val  + 5,  val  + 6,  val  + 7,
        addr + 7,  val  + 1,  val  + 2,  val  + 3,
        &len,      addr + 8,  addr + 9,  addr + 10,
        addr + 11, addr + 0,  addr + 1,  addr + 2,
        addr + 3,  addr + 12, addr + 13, addr + 14,
        val  + 4,  addr + 4,  addr + 5,  addr + 6,
    };
    
    ushort * maps8[LENGTH8] = {
        val  + 0,  val  + 5,  val  + 6,  val  + 7,
        addr + 7,  val  + 1,  val  + 2,  val  + 3,
        &len,      addr + 8,  addr + 9,  addr + 10,
        addr + 11, addr + 0,  addr + 1,  addr + 2,
        addr + 3,  addr + 12, addr + 13, addr + 14,
        cmp  + 4,  addr + 4,  addr + 5,  addr + 6,
        cmp  + 0,  cmp  + 5,  cmp  + 6,  cmp  + 7,
        val  + 4,  cmp  + 1,  cmp  + 2,  cmp  + 3,
    };
    
    ushort ** maps;
    if (length == 6) {
        maps = maps6;
        codeOut->len = 6;
    } else /* length == 8 */ {
        maps = maps8;
        codeOut->len = 8;
    }
    
    for (int l = 0; l < length; l++) {
        char letter = codeIn[l];
        ushort nib = convertLetter(letter);
        if (nib == ERROR_INVALID_CHAR) {
            printf("ERROR: Invalid character \"%c\"\n", letter);
            return ERROR_INVALID_CHAR;
        }
        
        uint iOff = l * 4;
        *maps[iOff + 0] = (nib >> 3) & 1;
        *maps[iOff + 1] = (nib >> 2) & 1;
        *maps[iOff + 2] = (nib >> 1) & 1;
        *maps[iOff + 3] = (nib >> 0) & 1;
    }
    
    len = (len == 0) ? 6 : 8;
    if (len != length) {
        printf("ERROR: Lengths %d and %d do not match\n", len, length);
        return ERROR_INVALID_LEN;
    }
    
    // initialize output code
    codeOut->addr = 0;
    codeOut->val  = 0;
    codeOut->cmp  = 0;
    
    // compile the addr, val and cmp codes into integers
    // first, compile the address
    for (int a = ADDR_LEN - 1; a >= 0; a--) {
        ushort bitNum = ADDR_LEN - 1 - a;
        codeOut->addr |= (addr[a] & 1) << bitNum;
    }
    // next, the value
    for (int v = VAL_LEN - 1; v >= 0; v--) {
        ushort bitNum = VAL_LEN - 1 - v;
        codeOut->val |= (val[v] & 1) << bitNum;
    }
    // lastly, the compare value
    if (length == 8) {
        for (int c = CMP_LEN - 1; c >= 0; c--) {
            ushort bitNum = CMP_LEN - 1 - c;
            codeOut->cmp |= (cmp[c] & 1) << bitNum;
        }
    }
    
    return CONVERSION_SUCCESS;
}

void printBinary(ushort value) {
    for (int v = sizeof(ushort) * 8 - 1; v >= 0; v--) {
        ushort bit = (value >> v) & 1;
        printf("%x", bit);
        if (v % 4 == 0) {
            printf(" ");
        }
    }
}

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
int main(int argc, char ** argv) {
    char testCodeIn[] = "SLXPLOVS";
    
    struct Code codeOut;
    int status = decode(testCodeIn, 8, &codeOut);
    
    if (status != CONVERSION_SUCCESS) {
        return EXIT_FAILURE;
    }
    
    ushort len  = codeOut.len;
    ushort addr = codeOut.addr;
    ushort val  = codeOut.val;
    ushort cmp  = codeOut.cmp;
    
    printf("Length:  ");
    printBinary(len);
    printf("\n");
    
    printf("Address: ");
    printBinary(addr);
    printf("\n");
    
    printf("Value:   ");
    printBinary(val);
    printf("\n");
    
    printf("Compare: ");
    printBinary(cmp);
    printf("\n");
    
    if (len == 6) {
        printf("S%x:%x:%s\n", addr, val, testCodeIn);
    } else /* len == 8 */ {
        printf("SC%x:%x:%x:%s\n", addr, val, cmp, testCodeIn);
    }
}
