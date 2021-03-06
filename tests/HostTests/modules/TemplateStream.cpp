#include <HostTests.h>
#include <FlashString/TemplateStream.hpp>
#include <Data/Stream/MemoryDataStream.h>
#include <Data/Stream/SectionTemplate.h>

DEFINE_FSTR_LOCAL(template1, "Stream containing {var1}, {var2} and {var3}. {} {{}} {{12345")
DEFINE_FSTR_LOCAL(template1_1, "Stream containing value #1, value #2 and {var3}. {} {{}} {{12345")
DEFINE_FSTR_LOCAL(template1_2, "Stream containing value #1, value #2 and [value #3]. {} {{}} {{12345")

DEFINE_FSTR_LOCAL(template2, "This text should {disable}not {var1} really {var2:hello} again {enable}be missing.")
DEFINE_FSTR_LOCAL(template2_1, "This text should be missing.")

class TemplateStreamTest : public TestGroup
{
public:
	TemplateStreamTest() : TestGroup(_F("Stream"))
	{
	}

	void execute() override
	{
		TEST_CASE("template1.1")
		{
			FSTR::TemplateStream tmpl(template1);
			tmpl.onGetValue([](const char* name) -> String {
				if(FS("var1") == name) {
					return F("value #1");
				}
				if(FS("var2") == name) {
					return F("value #2");
				}
				return nullptr;
			});

			check(tmpl, template1_1);
		}

		TEST_CASE("template1.2")
		{
			FSTR::TemplateStream tmpl(template1);
			tmpl.setVar("var3", "[value #3]");
			tmpl.onGetValue([](const char* name) -> String {
				if(FS("var1") == name) {
					return F("value #1");
				}
				if(FS("var2") == name) {
					return F("value #2");
				}
				return nullptr;
			});

			check(tmpl, template1_2);
		}

		TEST_CASE("template2.1")
		{
			Serial.println(template2);
			FSTR::TemplateStream tmpl(template2);
			tmpl.onGetValue([&tmpl](const char* name) -> String {
				if(FS("disable") == name) {
					tmpl.enableOutput(false);
					return "";
				}
				if(FS("enable") == name) {
					tmpl.enableOutput(true);
					return "";
				}
				return nullptr;
			});

			check(tmpl, template2_1);
		}

		TEST_CASE("ut_template1")
		{
			SectionTemplate tmpl(new FlashMemoryStream(Resource::ut_template1_in_rst));
			REQUIRE(tmpl.sectionCount() == 1);
			tmpl.setDoubleBraces(true);
			tmpl.onGetValue([&tmpl](const char* name) -> String {
				debug_e("getValue(%s)", name);
				if(FS("emit_contents") == name) {
					return "1";
				}

				if(memcmp(name, "emit_", 5) == 0) {
					return "";
				}

				return nullptr;
			});

			check(tmpl, Resource::ut_template1_out1_rst);
		}
	}

private:
	void check(TemplateStream& tmpl, const FlashString& ref)
	{
		MemoryDataStream mem;
		auto len = mem.copyFrom(&tmpl);
		debug_i("Copied %u bytes", len);
		String output;
		REQUIRE(mem.moveString(output));
		debug_i("output.length() == %u", output.length());
		REQUIRE(output.length() == len);
		REQUIRE(output.length() == ref.length());
		REQUIRE(ref == output);
	}
};

void REGISTER_TEST(TemplateStream)
{
	registerGroup<TemplateStreamTest>();
}
