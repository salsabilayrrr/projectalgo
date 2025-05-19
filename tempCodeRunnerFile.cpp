FILE* file = fopen("DataPesanan.dat", "rb");
    if (!file) {
        cout << "Gagal membuka file.\n";
        return;
    }

    Pesanan tiket[100];
    int jmltiket = 0;
    while (fread(&tiket[jmltiket], sizeof(Pesanan), 1, file))
    {
        jmltiket++;
    }
    fclose(file);
