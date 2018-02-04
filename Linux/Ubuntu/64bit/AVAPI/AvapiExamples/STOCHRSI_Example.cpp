#include <string>
#include <iostream>
#include <sstream>
#include "Avapi/AvapiConnection.hpp"
#include "Avapi/TECHNICAL_INDICATOR/STOCHRSI.hpp"

using namespace std;
using namespace Avapi;

int main()
{
    string lastHttpRequest = "";
    AvapiConnection* avapi_connection;
    
    try
    {
        avapi_connection = AvapiConnection::getInstance();
        avapi_connection->set_ApiKey("Your Alpha Vantage API Key !!!!");
    }
    catch(AvapiConnectionError& e)
    {
        cout <<  e.get_error() << endl;
        return EXIT_FAILURE;
    }
    
    auto& QueryObject = avapi_connection->GetQueryObject_STOCHRSI();

    auto Response = QueryObject.Query(   
             "MSFT"
             ,Const_STOCHRSI_interval::n_60min
             ,"10"
             ,Const_STOCHRSI_series_type::open
             ,"2"
             ,"1"
             ,Const_STOCHRSI_fastdmatype::n_3);

    cout << endl <<  "******** RAW DATA STOCHRSI ********"<< endl;
    cout <<  Response.get_RawData() << endl << endl;

    cout << "******** STRUCTURED DATA STOCHRSI ********"<< endl;

    if(Response.get_Data().isError())
    {
        cerr << Response.get_Data().get_ErrorMessage() << endl;
    }
    else
    {
        auto& MetaData  = Response.get_Data().get_MetaData();
        auto& TechnicalIndicator = Response.get_Data().get_TechnicalIndicator();

        cout << "========================" << endl;
        cout << "Symbol: " <<  MetaData.get_Symbol() << endl;
        cout << "Indicator: " <<  MetaData.get_Indicator() << endl;
        cout << "LastRefreshed: " <<  MetaData.get_LastRefreshed() << endl;
        cout << "Interval: " <<  MetaData.get_Interval() << endl;
        cout << "TimePeriod: " <<  MetaData.get_TimePeriod() << endl;
        cout << "FastKPeriod: " <<  MetaData.get_FastKPeriod() << endl;
        cout << "FastDPeriod: " <<  MetaData.get_FastDPeriod() << endl;
        cout << "FastDMAType: " <<  MetaData.get_FastDMAType() << endl;
        cout << "SeriesType: " <<  MetaData.get_SeriesType() << endl;
        cout << "TimeZone: " <<  MetaData.get_TimeZone() << endl;
        cout << "========================" << endl;
        cout << "========================" << endl;

        for(auto& element : TechnicalIndicator)
        {
            cout << "FastK: " << element.get_FastK() << endl;
            cout << "FastD: " << element.get_FastD() << endl;
            cout << "DateTime: " << element.get_DateTime() << endl;
            cout << "========================" << endl;
        }
    }
    
	return EXIT_SUCCESS;
}
