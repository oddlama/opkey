#pragma once


namespace opkey {


class Settings {
private:
	size_t multisamples = config::defaultMultisamples;
	// TODO save, load to from nvs, use everywhere
};


} // namespace opkey
