#include <iostream>
#include <sstream>
#include <vector>


class vertex_t {
 private:
  unsigned vertex;
  bool** pole;

 public:
  vertex_t() {
    vertex = 0;
    pole = nullptr;
  }
  vertex_t(unsigned number) : vertex_t() {
    vertex = number;
    pole = new bool*[vertex];
    for (std::size_t i = 0; i < vertex; i++) {
      pole[i] = new bool[vertex];
    }
  }

  std::vector<unsigned> what_vertex(int index) {
    std::vector<unsigned> used, res;
    for (std::size_t i = 0; i < vertex; i++) {
      used.push_back(false);
    }
    how_vertex(index, used, res);
    return res;
  }

  void how_vertex(int index,
                  std::vector<unsigned>& used,
                  std::vector<unsigned>& res) {
    used[index] = true;
    res.push_back(index + 1);
    for (std::size_t i = 0; i < vertex; i++) {
      if (pole[index][i]) {
        if (!(used[i])) {
          how_vertex(i, used, res);
        }
      }
    }
  }
  void print_res(std::ostream& ostream, std::vector<unsigned> res) {
    for (unsigned i : res) {
      ostream << i << ' ';
    }
  }

  void read(std::istringstream& stream) {
    for (std::size_t i = 0; i < vertex; i++) {
      for (std::size_t j = 0; j < vertex; j++) {
        stream >> pole[i][j];
      }
    }
  }
  ~vertex_t() {
    for (std::size_t i = 0; i < vertex; ++i) {
      delete[] pole[i];
    }
    delete[] pole;
  }
};

int main() {
  std::string input{
      "0 1 0\n"
      "0 0 1\n"
      "0 0 0"};
  vertex_t v(3);
  std::istringstream istream{input};
  v.read(istream);

  std::vector<unsigned> result;
  result = v.what_vertex(0);
  std::ostringstream output;
  v.print_res(output, result);
}
