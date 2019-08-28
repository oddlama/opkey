#pragma once

#include "fmt.h"

#include <stdexcept>
#include <vector>
#include <stack>
#include <string_view>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


namespace opkey {


#ifndef NDEBUG
#define OPKEY_CONCAT_IMPL(x, y) x##y
#define OPKEY_MACRO_CONCAT(x, y) OPKEY_CONCAT_IMPL(x, y)
#define OPKEY_PROFILE(name) auto OPKEY_MACRO_CONCAT(automaticProfilerGuard_, __COUNTER__) = Profiler::GetInstance()(name)
#define OPKEY_PROFILE_SCOPE(name) auto OPKEY_MACRO_CONCAT(automaticProfilerGuard_, __COUNTER__) = Profiler::GetInstance()("@" name)
#define OPKEY_PROFILE_FUNCTION() OPKEY_PROFILE(__PRETTY_FUNCTION__)
#define OPKEY_PROFILE_INTERRUPT(name) auto OPKEY_MACRO_CONCAT(automaticProfilerGuard_, __COUNTER__) = Profiler::GetInstance()(name, ProfileInterruptFunctionTag{})
#define OPKEY_PROFILE_INTERRUPT_SCOPE(name) auto OPKEY_MACRO_CONCAT(automaticProfilerGuard_, __COUNTER__) = Profiler::GetInstance()("@" name, ProfileInterruptFunctionTag{})
#define OPKEY_PROFILE_INTERRUPT_FUNCTION() OPKEY_PROFILE_INTERRUPT(__PRETTY_FUNCTION__)


struct ProfileInterruptFunctionTag {};


class Profiler;

class ProfilerSectionGuard {
public:
	explicit ProfilerSectionGuard(Profiler& profiler, size_t section, size_t savedSection = -1) noexcept
		: profiler(profiler)
		, section(section)
		, savedSection(savedSection)
	{ }

	~ProfilerSectionGuard() noexcept;

	ProfilerSectionGuard(const ProfilerSectionGuard&) = delete;
	ProfilerSectionGuard(ProfilerSectionGuard&&) = delete;
	ProfilerSectionGuard& operator=(const ProfilerSectionGuard&) = delete;
	ProfilerSectionGuard& operator=(ProfilerSectionGuard&&) = delete;

private:
	Profiler& profiler;
	size_t section;
	size_t savedSection;
};


/**
 * A profiler to easily profile the application
 */
class Profiler {
	friend class ProfilerSectionGuard;

public:
	static std::array<Profiler, 2>& GetInstances() {
		static std::array<Profiler, 2> instances{};
		return instances;
	}

	static Profiler& GetInstance() {
		return GetInstances()[xPortGetCoreID()];
	}

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
		int64_t GetTotalTime() const noexcept { return totalTime; }
		int64_t GetMinTime() const noexcept { return minTime; }
		int64_t GetMaxTime() const noexcept { return maxTime; }

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

private:
	Profiler();

public:
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
	 * Returns a section guard for the given section id.
	 * The id parameter MUST BE a string literal.
	 */
	ProfilerSectionGuard operator()(std::string_view id, ProfileInterruptFunctionTag) {
		// Leave current section and save it, so we can re-enter it later.
		auto savedSection = currentSection;
		sections[currentSection].Leave();

		// Switch to root section and enter the given section
		currentSection = 0;
		return ProfilerSectionGuard{*this, EnterSection(id), savedSection};
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
	void LeaveSection(size_t section, size_t savedSection) noexcept;

private:
	std::vector<Section> sections{};
	size_t currentSection = 0;
	int64_t resetTime = 0;
};
#else // NDEBUG
struct Profiler {
	static std::array<Profiler, 2>& GetInstances() noexcept {
		static std::array<Profiler, 2> instances{};
		return instances;
	}
	static Profiler& GetInstance() noexcept {
		return GetInstances()[xPortGetCoreID()];
	}
	void Reset() noexcept { }
	void PrintSummary() noexcept { }
	int32_t GetResetTime() noexcept { return 0; }
};
#define OPKEY_PROFILE_SCOPE(name)
#define OPKEY_PROFILE_FUNCTION()
#define OPKEY_PROFILE_INTERRUPT_SCOPE(name)
#define OPKEY_PROFILE_INTERRUPT_FUNCTION()
#endif //NDEBUG


} // namespace opkey
