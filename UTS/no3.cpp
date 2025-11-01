#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// inisialisasi graf, dibuat private biar gak bisa diubah sembarangan
class Graph {
private:
    // tau dulu berapa simpul, dan juga jaraknya berapa antar simpul
    int jumlah_vertex;
    vector<vector<int>> matriks_adj;

public:
    // buat matrix 5x5
    Graph(int v) {
        jumlah_vertex = v;
        matriks_adj.resize(v, vector<int>(v, 0));
    }

    // i sama j terhubung, w itu bobotnya
    void tambah_edge(int i, int j, int bobot) {
        // kurangi satu biar indeks sesuai
        i--;
        j--;
        // cek dulu apakah di range 1 - 5??
        if (i >= 0 && i < jumlah_vertex && j >= 0 && j < jumlah_vertex) {
            // graf ga berarah jadi valuenya sama
            matriks_adj[i][j] = bobot;
            matriks_adj[j][i] = bobot; 
        }
    }

    void dfs_util(int current, vector<bool>& visited, char nama_kafe[]) {
        // tandai klo uda kunjungi
        visited[current] = true;
        cout << nama_kafe[current];

        // simpan tetangga yang terhubung
        vector<pair<int, int>> tetangga; // (jarak, index)
        // nyari semua
        for (int i = 0; i < jumlah_vertex; i++) 
        {
            // klo misal ada yang gak 0 berarti blm dikunjunggi, terus push back
            if (matriks_adj[current][i] != 0 && !visited[i]) 
            {
                tetangga.push_back({matriks_adj[current][i], i});
            }
        }

        // urutkan manual berdasarkan jarak terkecil
        for (int i = 0; i < (int)tetangga.size(); i++) {
            for (int j = i + 1; j < (int)tetangga.size(); j++) {
                if (tetangga[j].first < tetangga[i].first) {
                    auto temp = tetangga[i];
                    tetangga[i] = tetangga[j];
                    tetangga[j] = temp;
                }
            }
        }

        // rekursif ke tetangga berikutnya smpe akhirrr
        for (int k = 0; k < (int)tetangga.size(); k++) {
            int next = tetangga[k].second;
            if (!visited[next]) {
                cout << " -> ";
                // jadi setelah udah siap bakal dipanggil lagi fungsi yang dfs util berikutnya buat dikunjunggi
                dfs_util(next, visited, nama_kafe);
            }
        }
    }

    void dfs(int start, char nama_kafe[]) {
        // cari yg belum dikunjungi
        vector<bool> visited(jumlah_vertex, false);

        cout << "penjelajahan parul (dfs dari " << nama_kafe[start] << "):" << endl;
        dfs_util(start, visited, nama_kafe);
        cout << endl << endl;
    }

    void balik_vector(vector<int>& v) {
        int kiri = 0, kanan = v.size() - 1;
        while (kiri < kanan) {
            int temp = v[kiri];
            v[kiri] = v[kanan];
            v[kanan] = temp;
            kiri++;
            kanan--;
        }
    }

    void bfs_weighted(int start, int end, char nama_kafe[]) {
        vector<int> jarak(jumlah_vertex, 9999);
        vector<int> parent(jumlah_vertex, -1);
        queue<int> q;

        jarak[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < jumlah_vertex; v++) {
                if (matriks_adj[u][v] != 0) {
                    int new_dist = jarak[u] + matriks_adj[u][v];
                    if (new_dist < jarak[v]) {
                        jarak[v] = new_dist;
                        parent[v] = u;
                        q.push(v);
                    }
                }
            }
        }

        // rekonstruksi jalur
        vector<int> path;
        for (int v = end; v != -1; v = parent[v])
            path.push_back(v);
        balik_vector(path);

        // output
        cout << "jalur tercepat parul (bfs):" << endl;
        int total_jarak = 0;
        for (int i = 0; i < (int)path.size(); i++) {
            cout << "kafe " << nama_kafe[path[i]] << endl;
            if (i < (int)path.size() - 1) {
                int segmen = matriks_adj[path[i]][path[i + 1]];
                total_jarak += segmen;
                cout << segmen << "m" << endl;
            }
        }

        cout << endl << "jalur terpendek: ";
        for (int i = 0; i < (int)path.size(); i++) {
            cout << nama_kafe[path[i]];
            if (i < (int)path.size() - 1) cout << " -> ";
        }
        cout << endl;
        cout << "total langkah: " << path.size() - 1 << " edge" << endl;
        cout << "total jarak: " << total_jarak << " meter" << endl;
    }
};

int main() {
    // disini manggil struct, jadi dibuatlah 5x5
    Graph g(5);
    char nama_kafe[5] = {'A', 'B', 'C', 'D', 'E'};

    // 
    g.tambah_edge(1, 2, 4); // A-B (4)
    g.tambah_edge(1, 3, 2); // A-C (2)
    g.tambah_edge(2, 4, 3); // B-D (3)
    g.tambah_edge(3, 4, 1); // C-D (1)
    g.tambah_edge(4, 5, 5); // D-E (5)

    // dfs dari A (index 0)
    g.dfs(0, nama_kafe);

    // bfs dari A ke E (index 0 ke 4)
    g.bfs_weighted(0, 4, nama_kafe);
}