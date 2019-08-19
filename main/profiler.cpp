#include "profiler.h"

#include <esp_timer.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


namespace OpKey {


#ifndef NDEBUG
ProfilerSectionGuard::~ProfilerSectionGuard() noexcept {
	profiler.LeaveSection(section, savedSection);
}


void Profiler::Section::Enter() {
	++enterCount;
	enterTime = esp_timer_get_time();
}

size_t Profiler::Section::Leave() {
	auto diff = esp_timer_get_time() - enterTime;
	totalTime += diff;
	if (diff < minTime) {
		minTime = diff;
	}
	if (diff > maxTime) {
		maxTime = diff;
	}
	return parent;
}


Profiler::Profiler() {
	esp::logi("Initializing profiler");
	sections.reserve(128);
	Reset();
}

void Profiler::Reset() {
	if (currentSection != 0) {
		throw std::runtime_error("Cannot call Profiler::Reset() within section '{}'"_format(sections[currentSection].GetName()));
	}

	// Delete all sections but the root section,
	// and record current time
	sections.clear();
	sections.emplace_back("root", 0, 0);
	resetTime = esp_timer_get_time();
}

void Profiler::PrintSummary() {
	if (currentSection != 0) {
		throw std::runtime_error("Cannot call Profiler::PrintSummary() within section '{}'"_format(sections[currentSection].GetName()));
	}

	auto Percent = [](double a, double b) {
		return a / b * 100.0;
	};

	int64_t totalTime = esp_timer_get_time() - resetTime;
	size_t totalCalls = 0;
	for (auto& section : sections) {
		totalCalls += section.GetEnterCount();
	}

	fmt::print("+--------------------+--------------------------------------------------------------------------------------------+\n");
	fmt::print("| PROFILING SUMMARY  | (total time: {:10d}us)   (total calls: {:8d})                                       |\n", totalTime, totalCalls);
	fmt::print("+--------------------+----------------------+------------------------+--------------+--------------+--------------+\n");
	fmt::print("| call count         | time w/o children    | Σ sum                  | Ø avg        | > min        | < max        |\n");
	fmt::print("+--------------------+----------------------+------------------------+--------------+--------------+--------------+\n");

	for (size_t i = 1; i < sections.size(); ++i) {
		auto& section = sections[i];
		fmt::print("| {:8d}({:7.3f}%) | {:8d}us({:7.3f}%) | Σ {:8d}us({:7.3f}%) | Ø {:8d}us | > {:8d}us | < {:8d}us | {:s}\n"
			, section.GetEnterCount()
			, Percent(section.GetEnterCount(), totalCalls)
			, 0 //sectionMinusChildrenTime
			, 0.0 //sectionMinusChildrenPercent
			, section.GetTotalTime()
			, Percent(section.GetTotalTime(), totalTime)
			, (section.GetEnterCount() > 0) ? (section.GetTotalTime() / section.GetEnterCount()) : 0
			, section.GetMinTime()
			, section.GetMaxTime()
			, section.GetName()
			);
	}

	fmt::print("+--------------------+----------------------+------------------------+--------------+--------------+--------------+\n");
}

size_t Profiler::EnterSection(std::string_view id) {
	size_t childSection = 0;
	for (size_t i = 0; i < sections.size(); ++i) {
		auto& section = sections[i];

		// Check for correct depth and id
		if (section.GetDepth() == sections[currentSection].GetDepth() + 1
				&& section.GetName() == id)
		{
			childSection = i;
			break;
		}
	}

	// If no section exists already, create a new one
	if (childSection == 0) {
		childSection = sections.size();
		sections.emplace_back(id, currentSection, sections[currentSection].GetDepth() + 1);
	}

	sections[childSection].Enter();
	return currentSection = childSection;
}

void Profiler::LeaveSection(size_t section, size_t savedSection) noexcept {
	if (currentSection != section) {
		esp::loge("Profiler::LeaveSection() called with invalid section '{}', while within '{}'\nAborting.", sections[section].GetName(), sections[currentSection].GetName());
		abort();
	} else if (currentSection == 0) {
		esp::loge("Profiler::LeaveSection() called while already at root.\nAborting.");
		abort();
	}

	auto leaveToSection = sections[currentSection].Leave();
	if (savedSection == -1) {
		currentSection = leaveToSection;
	} else {
		// After leaving the given section, re-enter and switch to the saved section
		currentSection = savedSection;
		sections[currentSection].Enter();
	}
	// TODO track total time in section and real time in section (LeaveForChild EnterAfterChild virtualleave virtualenter)
}
#endif // NDEBUG


} // namespace OpKey
