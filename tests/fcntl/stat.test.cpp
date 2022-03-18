#include <catch2/catch.hpp>
#include <lpipp/shm.hpp>

#define QUOTE(s) #s
#define NAME "/fcntl.stat" QUOTE(__LINE__)

using namespace lpipp;
using namespace shm_constants;

TEST_CASE("fcntl stat") {
  auto const name = NAME;

  auto const shared_memory = shm::open(name, ReadWrite | Create, 0600);
  REQUIRE(shared_memory);
  auto const shm_stat = shared_memory->stat();
  CHECK(shm_stat);
  CHECK(shm_stat->st_mode == 0100600);

  auto const same_shared_memory = shm::open(name, ReadOnly);
  CHECK(shared_memory);
  auto const same_shm_stat = same_shared_memory->stat();
  CHECK(same_shm_stat);
  CHECK(same_shm_stat->st_mode == 0100600);
  CHECK(same_shm_stat->st_ino == shm_stat->st_ino);

  CHECK(shm::unlink(name));
}
