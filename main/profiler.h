#pragma once


namespace OpKey {


struct ProfilerSectionGuard {
	explicit ProfilerSectionGuard() noexcept {
		profiler.
	}
	~ProfilerSectionGuard() noexcept {
	}
};


/**
 * A profiler to easily profile the application
 */
class Profiler {
private:
};


/**
 * A dummy profiler used to easily disable profiling without overhead.
 */
class DummyProfiler {
private:
};


} // namespace OpKey
