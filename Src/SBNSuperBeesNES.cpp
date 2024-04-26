#include "SBNSuperBeesNES.h"

#ifdef SBN_USE_WINDOWS
#include "Input/SBNDirectInput8.h"
#include "Audio/SBNAudio.h"
#include "Windows/Layout/SBNLayoutManager.h"
#include "Windows/MainWindow/SBNMainWindow.h"
#include "Windows/MainWindow/SBNMainWindowLayout.h"
#endif	// #ifdef SBN_USE_WINDOWS

#ifdef SBN_CPU_VERIFY
#include "File/SBNStdFile.h"
#endif	// #ifdef SBN_CPU_VERIFY


#if !defined( SBN_CPU_VERIFY )
#ifdef SBN_USE_WINDOWS
int WINAPI wWinMain( _In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE /*_hPrevInstance*/, _In_ LPWSTR /*_lpCmdLine*/, _In_ int /*_nCmdShow*/ ) {
	lsw::CBase::Initialize( _hInstance, new sbn::CLayoutManager(),
		L"LSNDOCK",
		L"LSNSPLITTER",
		L"LSNMULTISPLITTER",
		L"LSNTREEVIEW",
		L"LSNTREELISTVIEW",
		L"LSNCHILDWINDOW" );
	sbn::CDatabase::Init();
	sbn::CDirectInput8::CreateDirectInput8();
	sbn::CAudio::InitializeAudio();

	std::atomic_bool abIsAlive = false;
	sbn::CMainWindow * pwMainWindow = static_cast<sbn::CMainWindow *>(sbn::CMainWindowLayout::CreateMainWindow( &abIsAlive ));

	// Controls seconds_since_start(), milliseconds_since_start(), etc., Expression Evaluator.
	// We move it up as close to the start of the loop as possible so that these values most closely mark the actual time that meaningful execution
	//	takes place (clock() returns the time since the EXE actually started (before main() is even called), so we don't need more tickers from that
	//	time).
	// In a way, this allows (clock() - milliseconds_since_start()) to print the time it takes to initialize.
	ee::CExpEval::InitializeExpressionEvaluatorLibrary();
	MSG mMsg = {};
	::PeekMessageW( &mMsg, NULL, 0U, 0U, PM_NOREMOVE );

	while ( mMsg.message != WM_QUIT ) {
		// Use ::PeekMessage() so we can use idle time to render the scene.
		while ( (::PeekMessageW( &mMsg, NULL, 0U, 0U, PM_REMOVE ) != 0) ) {
			// Translate and dispatch the message.
			if ( !abIsAlive ) { break; }
			if ( ::TranslateAcceleratorW( pwMainWindow->Wnd(), NULL, &mMsg ) == 0 ) {
				::TranslateMessage( &mMsg );
				::DispatchMessageW( &mMsg );
			}
		}
		if ( !abIsAlive ) { break; }
		if ( mMsg.message != WM_QUIT ) {
			pwMainWindow->Tick();
		}
	}

	sbn::CAudio::ShutdownAudio();
	lsw::CBase::ShutDown();
	sbn::CDatabase::Reset();
	sbn::CDirectInput8::Release();
	return static_cast<int>(mMsg.wParam);
}
#endif	// #ifdef SBN_USE_WINDOWS
#else	// #if !defined( SBN_CPU_VERIFY )
#include "Bus/SBNBusA.h"
#include "Cpu/SBNCpu65816.h"
#include "LSONJson.h"
int WINAPI wWinMain( _In_ HINSTANCE /*_hInstance*/, _In_opt_ HINSTANCE /*_hPrevInstance*/, _In_ LPWSTR /*_lpCmdLine*/, _In_ int /*_nCmdShow*/ ) {
	std::unique_ptr<sbn::CBusA> pbBus = std::make_unique<sbn::CBusA>();
	pbBus->ApplyBasicMap();
	std::unique_ptr<sbn::CCpu65816> pcCpu = std::make_unique<sbn::CCpu65816>( (*pbBus.get()) );

	std::wstring wsBuffer;
	const DWORD dwSize = 0xFFFF;
	wsBuffer.resize( dwSize + 1 ); 
	::GetModuleFileNameW( NULL, wsBuffer.data(), dwSize );
	PWSTR pwsEnd = std::wcsrchr( wsBuffer.data(), L'\\' ) + 1;
	std::wstring wsRoot = wsBuffer.substr( 0, pwsEnd - wsBuffer.data() );
	{
		static wchar_t wChars[2] = { L'n', L'e' };
		for ( uint32_t I = 0x0A; I < 256; ++I ) {
			std::wstring wsFile;
			lson::CJson jSon;
			std::vector<uint8_t> vBytes;
			sbn::CStdFile sfFile;
			wchar_t wcFile[64];
			for ( size_t N = 0; N < SBN_ELEMENTS( wChars ); ++N ) {
				std::swprintf( wcFile, L"..\\..\\Research\\65816\\v1\\%.2X.%c.json", I, wChars[N] );
				if ( sfFile.Open( reinterpret_cast<const char16_t *>((wsRoot + wcFile).c_str()) ) ) {
					//sbn::CStdFile::LoadToMemory( L"J:\\My Projects\\L. Spiro NES\\Research\\nes6502\\v1\\02.json", vBytes );
					sfFile.LoadToMemory( vBytes );
					vBytes.push_back( 0 );

					if ( !jSon.SetJson( reinterpret_cast<const char *>(vBytes.data()) ) ) {
						::OutputDebugStringA( "JSON FAIL\r\n" );
					}
					else {
						pcCpu->ResetToKnown();
						pbBus->ApplyBasicMap();

						const lson::CJsonContainer::LSON_JSON_VALUE & jvRoot = jSon.GetContainer()->GetValue( jSon.GetContainer()->GetRoot() );
						for ( size_t J = 0; J < jvRoot.vArray.size(); ++J ) {
							const lson::CJsonContainer::LSON_JSON_VALUE & jvThis = jSon.GetContainer()->GetValue( jvRoot.vArray[J] );
							if ( !pcCpu->RunJsonTest( jSon, jvThis ) ) {
								volatile int hkhj = 0;
							}
						}

						::OutputDebugStringA( "JSON NOT FAIL\r\n" );
						::OutputDebugStringW( wcFile );
						::OutputDebugStringA( "\r\n" );
					}
				}
			}
		}
	}
	return 0;
}
#endif	// #if !defined( SBN_CPU_VERIFY )

#if 0
int wmain( int /*_iArgC*/, wchar_t * /*_pwcArgv*/[] ) {
#define SBN_PATH				u"J:\\My Projects\\L. Spiro NES\\Tests\\nestest.nes"
	//std::unique_ptr<sbn::CNtscSystem> pnsSystem = std::make_unique<sbn::CNtscSystem>();
	std::vector<uint8_t> vExtracted;
	std::u16string s16Path;
	{
		sbn::CZipFile fbFile;
		fbFile.Open( SBN_PATH );
		/*std::vector<uint8_t> vData;
		fbFile.LoadToMemory( vData );*/
		std::vector<std::u16string> vFiles;
		fbFile.GatherArchiveFiles( vFiles );
		if ( vFiles.size() ) {
			for ( auto I = vFiles.size(); I--; ) {
				std::u16string s16Ext = sbn::CUtilities::GetFileExtension( vFiles[I] );
				if ( ::_wcsicmp( reinterpret_cast<const wchar_t *>(s16Ext.c_str()), L"NES" ) == 0 ) {
					s16Path = sbn::CUtilities::GetFileName( vFiles[I] );
					fbFile.ExtractToMemory( vFiles[I], vExtracted );
					break;
				}
			}
		}
		else {
			s16Path = SBN_PATH;
			fbFile.LoadToMemory( vExtracted );
		}
	}
#undef SBN_PATH

	sbn::CClock cClock;
	/*pnsSystem->LoadRom( vExtracted, s16Path );
	pnsSystem->ResetState( false );*/
	uint64_t ui64TickCount = 0;
#define SBN_TIME								(1ULL * 10)
	while ( pnsSystem->GetAccumulatedRealTime() / pnsSystem->GetClockResolution() < SBN_TIME ) {
		pnsSystem->Tick();
		++ui64TickCount;
	}
	uint64_t ui64Time = cClock.GetRealTick() - cClock.GetStartTick();
	// If there are more Tick()'s than cycles then we definitely didn't go slower than the real system, so we can shave off excess time.

	double dTime = (ui64TickCount >= pnsSystem->GetMasterCounter()) ?
		double( SBN_TIME ) :
		ui64Time / double( cClock.GetResolution() );
	char szBuffer[256];
	::sprintf_s( szBuffer, "Ticks: %llu. Time: %.8f.\r\n"
		"Master Cycles: %llu (%.8f per second; expected %.8f).\r\n"
		"%.8f cycles per Tick().\r\n"
		"%.8f FPS.\r\n",
		ui64TickCount, dTime,
		pnsSystem->GetMasterCounter(), pnsSystem->GetMasterCounter() / dTime, double( pnsSystem->MasterHz() ) / pnsSystem->MasterDiv(),
		pnsSystem->GetMasterCounter() / double( ui64TickCount ),
		pnsSystem->GetPpu().GetFrameCount() / dTime
		);
	::OutputDebugStringA( szBuffer );
	return 0;
}
#endif	// #if 0
