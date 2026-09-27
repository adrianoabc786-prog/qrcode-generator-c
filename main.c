#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <qrencode.h>

void imprimirQRCode(QRcode *qrcode) {
    int largura = qrcode->width;
    unsigned char *data = qrcode->data;

    printf("\n");
    for (int i = 0; i < largura + 4; i++) printf("██");
    printf("\n");

    for (int y = 0; y < largura; y++) {
        printf("██");
        for (int x = 0; x < largura; x++) {
            if (*data & 1) {
                printf("  ");
            } else {
                printf("██");
            }
            data++;
        }
        printf("██\n");
    }

    for (int i = 0; i < largura + 4; i++) printf("██");
    printf("\n\n");
}

int main() {
    char texto[500];

    printf("Digite o texto ou URL para gerar o QR Code: ");
    if (fgets(texto, sizeof(texto), stdin) != NULL) {
        texto[strcspn(texto, "\n")] = '\0';
    }

    QRcode *qrcode = QRcode_encodeString(texto, 0, QR_ECLEVEL_L, QR_MODE_8, 1);

    if (qrcode == NULL) {
        printf("Erro ao gerar o QR Code.\n");
        return 1;
    }

    imprimirQRCode(qrcode);

    QRcode_free(qrcode);

    return 0;
}
