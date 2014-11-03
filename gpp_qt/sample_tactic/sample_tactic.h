#ifdef SAMPLE_TACTIC
class _declspec(dllexport) tactic //导出类point
#else
class _declspec(dllimport) tactic //导入类point
#endif

class tactic
{
		tactic();
		void readquote(std::string);
		
};


