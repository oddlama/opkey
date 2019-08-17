#include "profiler.h"

#include <esp_timer.h>


namespace OpKey {


ProfilerSectionGuard::~ProfilerSectionGuard() noexcept {
	profiler.LeaveSection(section);
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

	fmt::print("[[== PROFILE SUMMARY ==]]\n");
	fmt::print("total time: {:d}us\n", totalTime);
	fmt::print("total calls: {:d}\n", totalCalls);
	fmt::print("[relative us(%)] [calls cnt(%)] - <name>: total us(%), mean us, min us, max us\n");

	for (auto& section : sections) {
		fmt::print("[{:8d}us({:6.3f}%)] [{:8d}({:6.3f}%)] - {:s}: {:8d}us({:6.3f}%), {:8d}us, {:8d}us, {:8d}us\n"
			, 0 //sectionMinusChildrenTime
			, 0.0 //sectionMinusChildrenPercent
			, section.GetEnterCount()
			, Percent(section.GetEnterCount(), totalCalls)
			, section.GetName()
			, section.GetTotalTime()
			, Percent(section.GetTotalTime(), totalTime)
			, section.GetTotalTime() / section.GetEnterCount()
			, section.GetMinTime()
			, section.GetMaxTime()
			);
	}
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

void Profiler::LeaveSection(size_t section) noexcept {
	if (currentSection != section) {
		esp::loge("Profiler::LeaveSection() called with invalid section '{}', while within '{}'\nAborting.", sections[section].GetName(), sections[currentSection].GetName());
		abort();
	} else if (currentSection == 0) {
		esp::loge("Profiler::LeaveSection() called while already at root.\nAborting.");
		abort();
	}

	currentSection = sections[currentSection].Leave();
	// TODO track total time in section and real time in section (LeaveForChild EnterAfterChild virtualleave virtualenter)
}


} // namespace OpKey
