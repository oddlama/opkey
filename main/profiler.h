#pragma once

#include "fmt.h"

#include <stdexcept>
#include <vector>
#include <string_view>


namespace OpKey {


class Profiler;

class ProfilerSectionGuard {
public:
	explicit ProfilerSectionGuard(Profiler& profiler, size_t section) noexcept
		: profiler(profiler)
		, section(section)
	{ }

	~ProfilerSectionGuard() noexcept;

	ProfilerSectionGuard(const ProfilerSectionGuard&) = delete;
	ProfilerSectionGuard(ProfilerSectionGuard&&) = delete;
	ProfilerSectionGuard& operator=(const ProfilerSectionGuard&) = delete;
	ProfilerSectionGuard& operator=(ProfilerSectionGuard&&) = delete;

private:
	Profiler& profiler;
	size_t section;
};


/**
 * A profiler to easily profile the application
 */
class Profiler {
	friend class ProfilerSectionGuard;

private:
	class Section {
		friend class Profiler;

	public:
		Section(std::string_view name, size_t parent, size_t depth) noexcept
			: name(name)
			, parent(parent)
			, depth(depth)
		{ }

		std::string_view GetName() const noexcept { return name; }
		size_t GetDepth() const noexcept { return depth; }
		size_t GetEnterCount() const noexcept { return enterCount; }
		int64_t GetTotalTime() const noexcept { return totalTime;  }
		int64_t GetMinTime() const noexcept { return minTime;    }
		int64_t GetMaxTime() const noexcept { return maxTime;    }

	private:
		void Enter();
		size_t Leave();

	private:
		std::string_view name;
		size_t parent;
		size_t depth;

		size_t enterCount = 0;
		int64_t enterTime = -1;

		int64_t totalTime = 0;
		int64_t minTime = std::numeric_limits<int64_t>::max();
		int64_t maxTime = 0;
	};

public:
	Profiler();

	Profiler(const Profiler&) = delete;
	Profiler(Profiler&&) = delete;
	Profiler& operator=(const Profiler&) = delete;
	Profiler& operator=(Profiler&&) = delete;

	/**
	 * Returns a section guard for the given section id.
	 * The id parameter MUST BE a string literal.
	 */
	ProfilerSectionGuard operator()(std::string_view id) {
		return ProfilerSectionGuard{*this, EnterSection(id)};
	}

	/**
	 * Resets all recorded information
	 */
	void Reset();

	/**
	 * Prints a summary of the recorded information
	 */
	void PrintSummary();

	/**
	 * Gets the time of the last reset.
	 */
	int64_t GetResetTime() const noexcept {
		return resetTime;
	}

private:
	size_t EnterSection(std::string_view id);
	void LeaveSection(size_t section) noexcept;

private:
	std::vector<Section> sections{};
	size_t currentSection = 0;
	int64_t resetTime = 0;
};


/**
 * A dummy profiler used to easily disable profiling without overhead.
 */
class DummyProfiler {
private:
};


} // namespace OpKey
