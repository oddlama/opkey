#include <atomic>


namespace opkey {


class Spinlock {
public:
	void lock() {
		while (flag.test_and_set(std::memory_order_acquire)) {
			; // Spin
		}
	}

	void unlock() {
		flag.clear(std::memory_order_release);
	}

private:
	std::atomic_flag flag = ATOMIC_FLAG_INIT;
};


} // namespace opkey
