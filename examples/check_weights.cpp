#include <iostream>
#include <openssl/md5.h>

#include "darknet.h"
#include "layer.h"

using namespace std;

void print_md5_sum(unsigned char* md)
{
    for (auto i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        printf("%02x", md[i]);
    }
}

int main(int argc, char** argv)
{
    if (argc < 3) {
        cerr << "usage: chkweights cfgfile weightfile" << endl;
        exit(1);
    }

    auto* net = parse_network_cfg(argv[1]);
    load_weights(net, argv[2]);

    unsigned char result[MD5_DIGEST_LENGTH];

    for (auto i = 0; i < net->n; ++i) {
        const auto& layer = net->layers[i];
        if (layer.nweights) {
            MD5((uint8_t*) layer.weights, layer.nweights * sizeof(float), result);
            printf("layer 0x%.2x, type: 0x%.2x, weights: 0x", i, layer.type);
            print_md5_sum(result);

            if (layer.nbiases) {
                MD5((uint8_t*) layer.biases, layer.nbiases * sizeof(float), result);
                printf(", biases: 0x");
                print_md5_sum(result);
            }

            printf("\n");
        }
    }

    return 0;
}