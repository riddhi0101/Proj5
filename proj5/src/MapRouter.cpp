#include "MapRouter.h"
#include <cmath>
#include "XMLReader.h"
#include "XMLEntity.h"
#include <algorithm>
#include <ostream>
#include "CSVReader.h"
#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <vector>         // std::vector
#include <deque>
#include <queue>
#include <limits>
#include <utility>
#include <cmath>

const CMapRouter::TNodeID CMapRouter::InvalidNodeID = -1;

CMapRouter::CMapRouter(){

}

CMapRouter::~CMapRouter(){

}
double CMapRouter::Dijsktras(TNodeIndex src, TNodeIndex dest,std::vector<TNodeID>&path,int check){
    int sizeofnodes = Nodes.size();
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    std:: vector<double> distancecheck(Nodes.size(),std::numeric_limits<double>::max());
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    std:: vector<long> previous(Nodes.size(),-1);
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    auto CompareLambda = [&distancecheck](TNodeIndex idx1, TNodeIndex idx2){ return distancecheck[idx1] <distancecheck[idx2];};
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    TNodeIndex srcindex= src;
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    std::cout<< srcindex<<std::endl;
    distancecheck[srcindex] = 0.00000;
    previous[srcindex] = srcindex;
    std:: vector <TNodeIndex> Heap;
    //std::make_heap (Heap.begin(),Heap.end(), CompareLambda);
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    //std::priority_queue <TNodeIndex, std::vector<TNodeIndex>, CompareLambda > Heap;
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    Heap.push_back(srcindex);
    //std::push_heap (Heap.begin(),Heap.end());
    while(!Heap.empty()){
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        std::make_heap(Heap.begin(), Heap.end(), CompareLambda);
        std::pop_heap(Heap.begin(), Heap.end(), CompareLambda);
        auto Cur = Heap.back();
        Heap.pop_back();
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        std:: cout<< "cur = " << Cur<< std::endl;
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        //int Nodeindex1= NodeTranslation.find(Cur)->second;
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        auto Node1 = Nodes[Cur];
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        for (auto &edges1 : Node1.Edges){
            double Weight;
            switch(check){
                case 0: Weight = edges1.distance;
                        break;
                case 1: Weight = edges1.time;
                        break;
                default:Weight = edges1.distance/edges1.speedlimit;
                    std::cout<<"@ line: "<<__LINE__<<std::endl;
                        std::cout <<"driving distance is"<< edges1.distance <<std::endl;
                        std::cout <<"drving speedlimit is"<< edges1.speedlimit <<std::endl;
                        std::cout <<"driving time is"<< Weight <<std::endl;
                         break;
            }
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            std::cout<< "this is the other node of from " << Cur <<std::endl;
            std::cout<< edges1.OtherNode << std::endl;
            double altdistance = distancecheck[Cur]+ Weight;
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            if (altdistance < distancecheck[edges1.OtherNode]){
                //std::cout<<"@ line: "<<__LINE__<<std::endl;
                //auto edgeID = GetSortedNodeIDByIndex(Cur);
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                if (distancecheck[edges1.OtherNode] == std::numeric_limits<double>::max()) {
                    Heap.push_back(edges1.OtherNode);
                    //std::push_heap(Heap.begin(), Heap.end());
                }
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                distancecheck[edges1.OtherNode] = altdistance;
                //std::cout <<"altdistance added is "<<altdistance<<"for the node"<<edges1.OtherNode+1 <<"from the node "<<Node1.NodeID<<std::endl;
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                previous[edges1.OtherNode] = Cur;
                std::cout<<"@ line: "<<__LINE__<<std::endl;
            }


        }
        if (Cur == dest){
            break;
        }

    }
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    std::stack <TNodeID> maker;
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    maker.push(dest);
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    TNodeIndex prev = previous[dest];
    std::cout<<"@ line: "<<__LINE__<<std::endl;

    while(prev != srcindex){
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        maker.push(prev);
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        std::cout <<"error of prev is "<<prev<<std::endl;
        prev = previous[prev];
        std::cout<<"@ line: "<<__LINE__<<std::endl;

    }
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    maker.push(srcindex);
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    while(!maker.empty()){
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        //std::cout<<"the following is the maker stack "<< maker.top() <<std::endl;
        path.push_back(GetSortedNodeIDByIndex(maker.top()));
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        maker.pop();
    }
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    if (distancecheck[dest] == std::numeric_limits<double>::max() ){
        return -1;
    }
    return distancecheck[dest];
}
double CMapRouter::HaversineDistance(double lat1, double lon1, double lat2, double lon2){
    auto DegreesToRadians = [](double deg){return M_PI * (deg) / 180.0;};
    double LatRad1 = DegreesToRadians(lat1);
    double LatRad2 = DegreesToRadians(lat2);
    double LonRad1 = DegreesToRadians(lon1);
    double LonRad2 = DegreesToRadians(lon2);
    double DeltaLat = LatRad2 - LatRad1;
    double DeltaLon = LonRad2 - LonRad1;
    double DeltaLatSin = sin(DeltaLat/2);
    double DeltaLonSin = sin(DeltaLon/2);
    double Computation = asin(sqrt(DeltaLatSin * DeltaLatSin + cos(LatRad1) * cos(LatRad2) * DeltaLonSin * DeltaLonSin));
    const double EarthRadiusMiles = 3959.88;

    return 2 * EarthRadiusMiles * Computation;
}

double CMapRouter::CalculateBearing(double lat1, double lon1,double lat2, double lon2){
    auto DegreesToRadians = [](double deg){return M_PI * (deg) / 180.0;};
    auto RadiansToDegrees = [](double rad){return 180.0 * (rad) / M_PI;};
    double LatRad1 = DegreesToRadians(lat1);
    double LatRad2 = DegreesToRadians(lat2);
    double LonRad1 = DegreesToRadians(lon1);
    double LonRad2 = DegreesToRadians(lon2);
    double X = cos(LatRad2)*sin(LonRad2-LonRad1);
    double Y = cos(LatRad1)*sin(LatRad2)-sin(LatRad1)*cos(LatRad2)*cos(LonRad2-LonRad1);
    return RadiansToDegrees(atan2(X,Y));
}

bool CMapRouter::LoadMapAndRoutes(std::istream &osm, std::istream &stops, std::istream &routes){
    // Your code HERE
    CXMLReader Reader(osm);
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    SXMLEntity TempEntity;
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    Reader.ReadEntity(TempEntity);
    /*std::cout<<"@ line: "<<__LINE__<<std::endl;
    if((TempEntity.DType != SXMLEntity::EType::StartElement) or (TempEntity.DNameData != "osm")){
        std::cout<<"@ line: "<<__LINE__ <<"inside false loop" <<std::endl;
        return false;
    }*/
    std::cout<<"@ line: "<<__LINE__ <<std::endl;

    while (!Reader.End()) {
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        Reader.ReadEntity(TempEntity);
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        if (TempEntity.DType == SXMLEntity::EType::StartElement) {
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            if (TempEntity.DNameData == "node") {
                std::cout<<"@ line: "<<__LINE__<<"node loop" <<std::endl;
                TNodeID TempID = std::stoul(TempEntity.AttributeValue("id"));
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                double Templat = std::stod(TempEntity.AttributeValue("lat"));
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                double Templong = std::stod(TempEntity.AttributeValue("lon"));
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                Node TempNode;
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                TempNode.NodeID = TempID;
                TempNode.TLat = Templat;
                TempNode.TLong = Templong;
               // TempNode.mode = "Walk";
                NodeTranslation[TempID] = Nodes.size();
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                Nodes.push_back(TempNode);
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                SortedIDs.push_back(TempID);

            }
            else if (TempEntity.DNameData == "way") {

                bool OneWay = false;

                std::cout<<"@ line: "<<__LINE__<<std::endl;
                std::vector<TNodeIndex> WayNode;
                double SpeedLimit = 25.0;
                while (!Reader.End()) {

                    std::cout<<"@ line: "<<__LINE__<<std::endl;
                    Reader.ReadEntity(TempEntity,true);
                    std::cout<<"@ line: "<<__LINE__<<std::endl;
                    if (TempEntity.DType == SXMLEntity::EType :: StartElement){
                        std::cout<<"@ line: "<<__LINE__<<std::endl;
                        if(TempEntity.DNameData== "nd"){
                            std::cout<<"@ line: "<<__LINE__<< "inside nd loop"<<std::endl;
                            auto lookup = NodeTranslation.find(std::stoul(TempEntity.AttributeValue("ref")));
                            std::cout<<"@ line: "<<__LINE__<<std::endl;
                            if(NodeTranslation.end() != lookup){
                                std::cout<<"@ line: "<<__LINE__<<std::endl;
                                WayNode.push_back(lookup->second);
                            }
                        }
                        else if (TempEntity.DNameData== "tag"){
                            std::cout<<"@ line: "<<__LINE__<<"inside tag loop"<<std::endl;
                            auto key = TempEntity.AttributeValue("k");
                            auto value = TempEntity.AttributeValue("v");
                            if (key =="maxspeed"){
                                std::cout<<"@ line: "<<__LINE__<<std::endl;
                                SpeedLimit = std::stod (value);
                                std::cout<<"@ line: "<<SpeedLimit << "mph" <<std::endl;
                            }
                            else if (key == "oneway"){
                                std::cout<<"@ line: "<<__LINE__<<std::endl;
                                OneWay = value == "yes";
                                std::cout<<"@ line: "<<__LINE__<<std::endl;
                            }

                        }
                    }
                    if (TempEntity.DType == SXMLEntity::EType::EndElement){
                        std::cout<<"@ line: "<<__LINE__<<std::endl;
                        if (TempEntity.DNameData == "way"){
                            std::cout<<"@ line: "<<__LINE__<<std::endl;
                            break;
                        }
                    }
                }

                for (int i = 0; i < WayNode.size()-1; i++ ){
                    std::cout<<"@ line: "<<__LINE__<<std::endl;
                    Edge newEdge;
                    std::cout<<"@ line: "<<__LINE__<<std::endl;
                    std::cout<<"@ line: "<<__LINE__<<std::endl;
                    //auto nodeind = NodeTranslation.find(WayNode[i])->second;
                    newEdge.OtherNode = WayNode[i+1];
                    std::cout<<"@ line: "<<__LINE__<<std::endl;
                    double dist = HaversineDistance(Nodes[WayNode[i]].TLat, Nodes[WayNode[i]].TLong,Nodes[WayNode[i+1]].TLat, Nodes[WayNode[i+1]].TLong);
                    std::cout<<"@ line: "<<__LINE__<<std::endl;
                    newEdge.distance = dist;
                    newEdge.speedlimit = SpeedLimit;
                    std::cout << SpeedLimit << "this is speed limit"<<std::endl;
                    newEdge.time = dist/3.00000;
                    Nodes[WayNode[i]].Edges.push_back(newEdge);
                    std::cout<<"@ line: "<<__LINE__<<std::endl;

                    if (!OneWay){
                        std::cout<<"@ line: "<<__LINE__<<std::endl;
                        //auto nodeind = NodeTranslation.find(WayNode[i])->second;
                        Edge newEdge1;
                        //auto nodeind2 = NodeTranslation.find(WayNode[i-1])->second;
                        newEdge1.OtherNode = WayNode[i];
                        newEdge1.distance = newEdge.distance;
                        std::cout<<"@ line: "<<__LINE__<<std::endl;
                        newEdge1.speedlimit = newEdge.speedlimit;
                        newEdge1.time = newEdge.time;
                        std::cout<<"@ line: "<<__LINE__<<std::endl;
                        Nodes[WayNode[i+1]].Edges.push_back(newEdge1);
                        std::cout<<"@ line: "<<__LINE__<<std::endl;
                    }
                }
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                WayNode.clear();

            }
        }
    }
    std::sort (SortedIDs.begin(),SortedIDs.end());
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    CCSVReader Reader1(stops);
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    std::vector <std::string> readingVector;
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    Reader1.ReadRow(readingVector);
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    while(!Reader1.End()){
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        Reader1.ReadRow(readingVector);
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        auto lookup1 = NodeTranslation.find(std::stoul(readingVector[1]));
        auto indexer = NodeTranslation.find(std::stoul(readingVector[1]))->second;
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        if(NodeTranslation.end() != lookup1) {
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            StopsMaps[std::stoul(readingVector[0])] = std::stoul(readingVector[1]);
            NodeIDtoStopID[std::stoul(readingVector[1])] = std::stoul(readingVector[0]);
            std::cout<<"@ line: "<<__LINE__<<std::endl;
        }
    }

    CCSVReader Reader2(routes);
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    std::vector <std::string> readingVector1;
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    std::cout<<std::boolalpha<< !Reader2.End()<<std::endl;
    Reader2.ReadRow(readingVector1);
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    std::cout<<std::boolalpha<< !Reader2.End()<<std::endl;
    while(!Reader2.End()){
        readingVector1.clear();
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        Reader2.ReadRow(readingVector1);
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        auto lookup2 = StopsMaps.find(std::stoul(readingVector1[1]));
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        if (StopsMaps.end() != lookup2){
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            if (BusRoutesmap.find(readingVector1[0]) != BusRoutesmap.end()){
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                std::cout << std::stoul(readingVector1[1])<<std::endl;
                BusRoutesmap.find(readingVector1[0])->second.push_back(std::stoul(readingVector1[1]));
                auto indexer = NodeTranslation.find(std::stoul(readingVector1[1]))->second;
                //Nodes[lookup1].mode = "bus";

                std::cout<<"@ line: "<<__LINE__<<std::endl;
            }else{
                routenames.push_back(readingVector1[0]);
                std::vector <TStopID> tempvector;
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                tempvector.push_back(std::stoul(readingVector1[1]));
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                BusRoutesmap[readingVector1[0]] = tempvector;
                std::cout<<"@ line: "<<__LINE__<<std::endl;
            }
        }

    }
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    for (auto &nodes2 : Nodes){
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        for (auto edg: nodes2.Edges){
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            BusEdge edge4;
            edge4.time  = edg.time;
            edge4.vehicle = "Walk";
            edge4.Otherbusnode = edg.OtherNode;
            edge4.busname = "Walk";
            nodes2.Busedge.push_back(edge4);
        }
    }
    std::cout<<"@ line: "<<__LINE__<<std::endl;

    for (auto  ch : routenames) {
        auto &vectorofstop = BusRoutesmap.find(ch)->second;
        std::cout << "@ line: " << __LINE__ << std::endl;
        for (int o = 0; o < vectorofstop.size() - 1; o++) {
            auto ider = StopsMaps.find(vectorofstop[o])->second;
            auto otherid = StopsMaps.find(vectorofstop[o + 1])->second;
            BusEdge bus;
            bus.vehicle = "bus";
            bus.busname = ch;
            auto nodeinde = NodeTranslation.find(ider)->second;
            auto othernodeindex = NodeTranslation.find(otherid)->second;
            bus.Otherbusnode = NodeTranslation.find(otherid)->second;
            std::vector <TNodeID> fun;
            double timex = 0.0;
            int checker1 = 0;
            for (auto &edges : Nodes[nodeinde].Edges) {
                if (edges.OtherNode == othernodeindex) {
                    bus.time = edges.distance / edges.speedlimit;
                    checker1++;
                }
            }
            if (checker1 == 0) {
                std::cout<< "this is fincalling dijkstra on "<< ider<<" "<<otherid<<std::endl;
                double time = Dijsktras(nodeinde, othernodeindex, fun,2);
                bus.time = time;
                bus.path1 = fun;

            }
            std::cout << "@ line: " << __LINE__ << std::endl;
            Nodes[nodeinde].Busedge.push_back(bus);
        }

    }
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    return true;

}

size_t CMapRouter::NodeCount() const{
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    return SortedIDs.size();
}

CMapRouter::TNodeID CMapRouter::GetSortedNodeIDByIndex(size_t index) const{
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    return SortedIDs[index];

}

CMapRouter::TLocation CMapRouter::GetSortedNodeLocationByIndex(size_t index) const{
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    if (index >= SortedIDs.size()){
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        return std::make_pair(180.0, 360.0);
    }
    else{
        auto tempIndex = NodeTranslation.find(SortedIDs[index])->second;
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        auto lat = Nodes[tempIndex].TLat;
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        auto longs = Nodes[tempIndex].TLong;
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        return std::make_pair(lat,longs);
    }

}

CMapRouter::TLocation CMapRouter::GetNodeLocationByID(TNodeID nodeid) const{
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    if (NodeTranslation.end() == NodeTranslation.find(nodeid)){
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        return std::make_pair(180.0, 360.0);

    }
    else{
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        auto tempIndex = NodeTranslation.find(nodeid)->second;
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        auto lat = Nodes[tempIndex].TLat;
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        auto longs = Nodes[tempIndex].TLong;
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        return std::make_pair(lat,longs);
    }
}

CMapRouter::TNodeID CMapRouter::GetNodeIDByStopID(TStopID stopid) const{
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    auto lookup = StopsMaps.find(stopid);
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    if (lookup != StopsMaps.end()){
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        return lookup->second;
    }
}

size_t CMapRouter::RouteCount() const{
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    return BusRoutesmap.size();
}

std::string CMapRouter::GetSortedRouteNameByIndex(size_t index) const{
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    //int index1 = int(index);
    auto iter = BusRoutesmap.begin();
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    auto iter1 = std::next(iter, index);
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    return iter1->first;

}

bool CMapRouter::GetRouteStopsByRouteName(const std::string &route, std::vector< TStopID > &stops){
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    auto lookup = BusRoutesmap.find(route);
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    if (lookup == BusRoutesmap.end()){
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        return false;
    }
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    stops = lookup->second;
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    return true;

}

double CMapRouter::FindShortestPath(TNodeID src, TNodeID dest, std::vector< TNodeID > &path){
    // Your code HERE
    TNodeIndex srcindex= NodeTranslation.find(src)->second;
    TNodeID destindex= NodeTranslation.find(dest)->second;
    double k = Dijsktras(srcindex,destindex,path,0);
    return k;
}


double CMapRouter::FindFastestPath(TNodeID src, TNodeID dest, std::vector< TPathStep > &path){
    int sizeofnodes = Nodes.size();
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    std:: vector<double> timecheck;
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    std:: vector<long> previous;
    std:: vector<long> edgesforbus;
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    for (int i =0; i<sizeofnodes;i++) {
        timecheck.push_back(std::numeric_limits<double>::max());
        previous.push_back(-1);
        std::cout<<"@ line: "<<__LINE__<<std::endl;
    }
    auto CompareLambda = [&timecheck](TNodeIndex idx1, TNodeIndex idx2){ return timecheck[idx1] <timecheck[idx2];};
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    TNodeIndex srcindex= NodeTranslation.find(src)->second;
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    std::cout<< srcindex<<std::endl;
    TNodeIndex destindex= NodeTranslation.find(dest)->second;
    timecheck[srcindex] = 0;
    previous[srcindex] = srcindex;

    std:: vector <TNodeIndex> Heap;
    std::make_heap (Heap.begin(),Heap.end(), CompareLambda);
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    //std::priority_queue <TNodeIndex, std::vector<TNodeIndex>, CompareLambda > Heap;
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    Heap.push_back(srcindex);
    std::push_heap (Heap.begin(),Heap.end());
    int thirtycheck =0;
    while(!Heap.empty()){
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        auto Cur = Heap.front();
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        std:: cout<< "cur = " << Cur<< std::endl;
        Heap.erase(Heap.begin());
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        //int Nodeindex1= NodeTranslation.find(Cur)->second;
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        auto Node1 = Nodes[Cur];
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        for (auto edges1 : Node1.Busedge){
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            std::cout<< "this is the other node of from " << Cur <<std::endl;
            std::cout<< edges1.Otherbusnode << std::endl;
            double alttime = timecheck[Cur]+ edges1.time;
            if (edges1.vehicle == "bus"){
                thirtycheck++;
                alttime = alttime + (30.0/3600.0);
            }
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            if (alttime < timecheck[edges1.Otherbusnode]){
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                //auto edgeID = GetSortedNodeIDByIndex(Cur);
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                if (timecheck[edges1.Otherbusnode] == std::numeric_limits<double>::max()) {
                    Heap.push_back(edges1.Otherbusnode);
                    std::push_heap(Heap.begin(), Heap.end());
                }
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                timecheck[edges1.Otherbusnode] = alttime;
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                previous[edges1.Otherbusnode] = Cur;
                std::cout<<"@ line: "<<__LINE__<<std::endl;

            }
        }
        if (Cur == destindex){
            break;
        }
    }

    if (timecheck[destindex] ==std::numeric_limits<double>::max() ){
        path.clear();
        return std::numeric_limits<double>::max();
    }
    std::cout<<"thirty seconds is added " << thirtycheck <<"many times"<<std::endl;
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    std::stack <TNodeIndex> maker;
    std::vector <TNodeIndex> path1;
    std::vector<TPathStep> buser;
    //double srcfinder;
    std::cout<<"@ line: "<<__LINE__<<std::endl;


    maker.push(destindex);
    TNodeIndex prev = previous[destindex];
    while(prev != srcindex){
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        maker.push(prev);
        std::cout <<"error of prev is "<<prev<<std::endl;
        prev = previous[prev];
    }
    maker.push(srcindex);
    while(!maker.empty()){
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        path1.push_back((maker.top()));
        maker.pop();
    }
    std::cout <<"the path1 size is"<<path1.size()<<std::endl;
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    std::vector <std::vector <std::string> > possiblepaths;
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    //int checker55 = 0;
    for (int dev = 0; dev <path1.size()-1; dev++){
        //checker55++;
        TNodeIndex indexx = path1[dev];
        //TNodeIndex nextindex = NodeTranslation.find(path1[dev+1]);
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        std::cout<< dev<< std::endl;
        std::vector <std::string> empt;
        for (auto edge1: Nodes[indexx].Busedge){
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            std::cout<<Nodes[indexx].NodeID<<  edge1.Otherbusnode +1 << edge1.vehicle <<std::endl;
            if (edge1.Otherbusnode == path1[dev+1]){
                std::string topush;
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                if (edge1.vehicle == "bus"){
                    topush = "Bus " + edge1.busname;
                }else{
                    topush = edge1.busname;
                }

                empt.push_back(topush);
                std::cout<<"@ line: "<<__LINE__<<std::endl;

            }
            std::sort(empt.begin(),empt.end());

        }
        possiblepaths.push_back(empt);
        empt.clear();
    }
    //std::cout<<"this is the checker "<< checker55 <<std::endl;
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    std::cout <<possiblepaths.size()<< std::endl;
    std::cout<<"@ line: "<<__LINE__<<std::endl;

    for (int k = 0; k< possiblepaths.size(); k++){
        std::cout<<"index of possible path " << k<<std::endl;
        for (auto i : possiblepaths[k]){
            std::cout<< i<< std:: endl;

        }
    }
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    std::pair <std::string,TNodeID> pusher1("Walk",src);
    path.push_back(pusher1);
    for(int y = 0; y < possiblepaths.size(); y++){
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        std::vector<std::string> vec = possiblepaths[y];
        bool done = false;

        if( vec[0]=="Walk"){
            TNodeID idx = Nodes[path1[y+1]].NodeID;
            std::pair <std::string,TNodeID> pusher("Walk",idx);
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            //pusher = std::make_pair <std::string,TNodeID>;
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            path.push_back(pusher);
            std::cout<<"@ line: "<<__LINE__<<std::endl;
        }
        else {
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            int checkj = 0;
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            std::vector <std::string> holder(26);
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            std::vector <TNodeID> nodeids;
            //std::vector <std::string> union1 =
            std::vector<std::string>::iterator it;
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            it = std::set_union(possiblepaths[y].begin(), possiblepaths[y].end(), possiblepaths[y + 1].begin(),
                                possiblepaths[y + 1].end(),holder.begin());
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            holder.resize(it - holder.begin());
            nodeids.push_back(Nodes[path1[y]].NodeID);
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            checkj++;
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            while ((holder.size() >= 0) and (y < possiblepaths.size())) {
                if( possiblepaths[y + 1][0]=="Walk"){
                    break;
                }

                std::cout<<"@ line: "<<__LINE__<<std::endl;
                std::vector <std::string> union1 = holder;
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                holder.clear();
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                std::vector <std::string> holder(26);
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                std::vector<std::string>::iterator it;
                std::cout<<"@ line: "<<__LINE__<<std::endl;

                it = std::set_intersection(union1.begin(), union1.end(), possiblepaths[y + 1].begin(),possiblepaths[y + 1].end(),holder.begin());
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                holder.resize(it - holder.begin());
                if (holder.size()==0){
                    holder = union1;
                    break;
                }
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                nodeids.push_back(Nodes[path1[y+1]].NodeID);
                y++;
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                checkj++;
                std::cout<<"@ line: "<<__LINE__<<std::endl;
            }
            std::cout <<"the holder breaker size is "<<holder.size()<<std::endl;

            for (int aq = 0; aq<checkj;aq++){
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                //std::cout <<"adding bus "<< holder[0]<<"to the node "<< nodeids[aq+1]<<std::endl;
                std::pair <std::string,TNodeID> pusher(holder[0],nodeids[aq+1]);
                //pusher = std::make_pair <std::string,TNodeID>;
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                path.push_back(pusher);
                std::cout<<"@ line: "<<__LINE__<<std::endl;
            }
            std::cout <<"this is y" <<y<<std::endl;
        }
    }
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    std::vector < std::pair <std::string, TNodeID> > holding;
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    int stop2 = path.size();
    for (int rr = 0; rr< stop2-1; rr++ ){
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        TNodeIndex firstnodeind = NodeTranslation.find(std::get<1> (path[rr]))->second;
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        TNodeIndex secondnodeind = NodeTranslation.find(std::get<1> (path[rr+1]))->second;
        std::cout<<"@ line: "<<__LINE__<<std::endl;
       for (auto kk:Nodes[firstnodeind].Busedge){
           std::cout<<"@ line: "<<__LINE__<<std::endl;
           std::cout<<"@ line: "<<__LINE__<<std::endl;
           if (kk.Otherbusnode == secondnodeind){
               std::cout<<"@ line: "<<__LINE__<<std::endl;
               if (kk.path1.size()>2){
                   std::cout<<"this is where size is greater than 2 on index "<< rr<< "of the path"<< kk.busname << std::endl;
                   std::cout<<"@ line: "<<__LINE__<<std::endl;
                   for (int i=1; i<kk.path1.size()-1; i++){
                       std::cout<<"@ line: "<<__LINE__<<std::endl;
                       std::pair <std::string, TNodeID> pushing (std::get <0>(path[rr]),kk.path1[i]);
                       holding.push_back(pushing);
                   }
                   std::cout<<"@ line: "<<__LINE__<<std::endl;
                   path.insert(path.begin()+rr+1, holding.begin(), holding.end());
                   rr +=holding.size();
                   holding.clear();

               }
               std::cout<<"@ line: "<<__LINE__<<std::endl;
           }
           std::cout<<"@ line: "<<__LINE__<<std::endl;
       }
        std::cout<<"@ line: "<<__LINE__<<std::endl;

    }

    std::cout<<"@ line: "<<__LINE__<<std::endl;
    return timecheck[destindex];
}

bool CMapRouter::GetPathDescription(const std::vector< TPathStep > &path, std::vector< std::string > &desc) const{
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    if (path.size()==0){
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        return false;
    }
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    std::string descript = "";
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    for (int v = 0; v <path.size();v++){
        std::cout<<"@ line: "<<__LINE__<<std::endl;
        if (v ==0){
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            //descript = "Start at " + std::to_string(std::get<1>(path[0]));
            double lat2 = Nodes[NodeTranslation.find(std::get<1>(path[0]))->second].TLat;
            double long2 = Nodes[NodeTranslation.find(std::get<1>(path[0]))->second].TLong;
            double lat1 = Nodes[NodeTranslation.find(std::get<1>(path[1]))->second].TLat;
            double long1 = Nodes[NodeTranslation.find(std::get<1>(path[1]))->second].TLong;
            long flooredlat = floor(lat1);
            long flooredlong = floor(long1);
            long flooredlat2 = floor(lat2);
            long flooredlong2 = floor(long2);
            std::string walking;
            std::string headinglat;
            std::string headinglong;
            std::string northmintue;
            std::string easternnmintue;
            std::string latadd;
            std::string longadd;
            std::string easternsecond;
            std::string northsecond;

            if (lat2-flooredlat2 ==0) {
                northmintue = "0\' ";
                northsecond = "0\" ";
                double lat2add1;
                if (lat2 < 0){
                    headinglat = "S, ";
                    lat2add1= lat2*-1;
                }
                else{
                    lat2add1= lat2;
                    headinglat = "N, ";
                }
                latadd = std::to_string(int(lat2add1))+"d ";
            }
            else{
                double latmin = (lat2-flooredlat2) * 60.0;
                double latminfloor = floor(latmin);
                if ((latmin-latminfloor)==0){
                    northsecond = "0\" ";
                    northmintue = std::to_string(int(latminfloor))+"\' ";
                    double lat2add1= lat2*-1;
                    if (lat2 < 0){
                        headinglat = "S, ";
                        lat2add1= lat2*-1;
                    }
                    else{
                        lat2add1= lat2;
                        headinglat = "N, ";
                    }
                    latadd = std::to_string(int(lat2add1))+"d ";
                }
                else{
                    double latsec = (latmin-latminfloor) * 60.0;
                    double latsecfloor = floor(latsec);
                    northmintue = std::to_string(latminfloor)+"\' ";
                    northsecond = std::to_string(latsecfloor)+"\" ";
                    double lat2add1;
                    if (lat2 < 0){
                        headinglat = "S, ";
                        lat2add1= lat2*-1;
                    }
                    else{
                        lat2add1= lat2*-1;
                        headinglat = "N, ";
                    }
                    latadd = std::to_string(int(lat2add1))+"d ";
                }
            }
            if (long2-flooredlong2 ==0) {
                easternnmintue = "0\' ";
                easternsecond = "0\" ";
                double long2add1= long2;
                if (long2<0){
                    headinglong = "W";
                    long2add1= long2*-1;
                }
                else{
                    headinglong = "E";
                }
                longadd = std::to_string(int(long2add1))+"d ";
            }
            else{
                double longmin = (long2-flooredlong2) * 60.0;
                double longminfloor = floor(longmin);
                if ((longmin-longminfloor)==0){
                    easternsecond = "0\" ";
                    easternnmintue = std::to_string(longminfloor)+"\' ";
                    double long2add1= long2;
                    if (long2<0){
                        headinglong = "W";
                        long2add1= long2*-1;
                    }
                    else{
                        headinglong = "E";
                    }
                    longadd = std::to_string(int(long2add1))+"d ";
                }
                else{
                    double longsec = (longmin-longminfloor) * 60.0;
                    double longsecfloor = floor(longsec);
                    easternnmintue = std::to_string(longminfloor)+"\' ";
                    easternsecond = std::to_string(longsecfloor)+"\" ";
                    double long2add1= long2;
                    if (long2<0){
                        headinglong = "W";
                        long2add1= long2*-1;
                    }
                    else{
                        headinglong = "E";
                    }
                    longadd = std::to_string(int(long2add1))+"d ";
                }
            }
            descript = "Start at "+ latadd+ northmintue+northsecond+headinglat+ longadd+easternnmintue+easternsecond+headinglong;
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            desc.push_back(descript);
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            descript = "";
        }
        else{
            std::cout<<"@ line: "<<__LINE__<<std::endl;
            if (std::get<0>(path[v]) != "Walk"){
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                bool done = false;
                TStopID stopid1 = -1;
                std::string checkpath = std::get<0>(path[v]);
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                while (!done){
                    std::cout<<"@ line: "<<__LINE__<<std::endl;
                    if (std::get<0>(path[v]) == checkpath){
                        std::cout<<"@ line: "<<__LINE__<<std::endl;
                        v++;
                        continue;
                    }
                    else{
                        v--;
                        std::cout<<"@ line: "<<__LINE__<<std::endl;
                        TNodeID nodetogetoff = std::get<1>(path[v]);
                        std::cout <<"getting the stop id of node:- "<<nodetogetoff<<std::endl;
                        stopid1 = NodeIDtoStopID.find(nodetogetoff)->second;
                        std::cout <<" the stop id of node:- "<<stopid1<<std::endl;
                        std::cout<<"@ line: "<<__LINE__<<std::endl;
                        done = true;
                    }
                }
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                descript =  "Take " + checkpath + " and get off at stop "+std::to_string(stopid1);
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                desc.push_back(descript);
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                descript = "";
            }
            else{
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                double lat1 = Nodes[NodeTranslation.find(std::get<1>(path[v-1]))->second].TLat;
                double long1 = Nodes[NodeTranslation.find(std::get<1>(path[v-1]))->second].TLong;
                double lat2 = Nodes[NodeTranslation.find(std::get<1>(path[v]))->second].TLat;
                double long2 = Nodes[NodeTranslation.find(std::get<1>(path[v]))->second].TLong;
                long flooredlat = floor(lat1);
                long flooredlong = floor(long1);
                long flooredlat2 = floor(lat2);
                long flooredlong2 = floor(long2);
                std::string walking;
                std::string headinglat;
                std::string headinglong;
                std::string northmintue;
                std::string easternnmintue;
                std::string latadd;
                std::string longadd;
                std::string easternsecond;
                std::string northsecond;
                double degree = CalculateBearing(lat1,long1,lat2,long2);
                std::cout <<"the degree is "<<degree<<" for the node "<< Nodes[NodeTranslation.find(std::get<1>(path[v-1]))->second].NodeID << " and "<< Nodes[NodeTranslation.find(std::get<1>(path[v]))->second].NodeID << std::endl;

                if (degree  > 112.5 and degree <= 157.5) {
                    walking = "SE ";
                } else if (degree > 22.5 and degree <= 67.5) {
                    walking = "NE ";
                } else if (degree >=-112.5 and degree < -157.5) {
                    walking = "SW ";
                } else if (degree >= -22.5 and degree < -67.5) {
                    walking = "NW ";
                } else if (degree > -22.5 and degree <= 22.5) {
                    walking = "N ";
                } else if (degree > 67.5 and degree <= 112.5) {
                    walking = "E ";
                } else if (degree <= -157.5 or degree > 157.5) {
                    walking = "S ";
                } else if (degree <= -67.5 and degree > -112.5){
                    walking = "W ";
                }
                if (lat2-flooredlat2 ==0) {
                    northmintue = "0\' ";
                    northsecond = "0\" ";
                    double lat2add1;
                    if (lat2 < 0){
                        headinglat = "S, ";
                        lat2add1= lat2*-1;
                    }
                    else{
                        lat2add1= lat2;
                        headinglat = "N, ";
                    }
                    latadd = std::to_string(int(lat2add1))+"d ";
                }
                else{
                    double latmin = (lat2-flooredlat2) * 60.0;
                    double latminfloor = floor(latmin);
                    if ((latmin-latminfloor)==0){
                        northsecond = "0\" ";
                        northmintue = std::to_string(int(latminfloor))+"\' ";
                        double lat2add1= lat2*-1;
                        if (lat2 < 0){
                            headinglat = "S, ";
                            lat2add1= lat2*-1;
                        }
                        else{
                            lat2add1= lat2;
                            headinglat = "N, ";
                        }
                        latadd = std::to_string(int(lat2add1))+"d ";
                    }
                    else{
                        double latsec = (latmin-latminfloor) * 60.0;
                        double latsecfloor = floor(latsec);
                        northmintue = std::to_string(latminfloor)+"\' ";
                        northsecond = std::to_string(latsecfloor)+"\" ";
                        double lat2add1;
                        if (lat2 < 0){
                            headinglat = "S, ";
                            lat2add1= lat2*-1;
                        }
                        else{
                            lat2add1= lat2*-1;
                            headinglat = "N, ";
                        }
                        latadd = std::to_string(int(lat2add1))+"d ";
                    }
                }
                if (long2-flooredlong2 ==0) {
                    easternnmintue = "0\' ";
                    easternsecond = "0\" ";
                    double long2add1= long2;
                    if (long2<0){
                        headinglong = "W";
                        long2add1= long2*-1;
                    }
                    else{
                        headinglong = "E";
                    }
                    longadd = std::to_string(int(long2add1))+"d ";
                }
                else{
                    double longmin = (long2-flooredlong2) * 60.0;
                    double longminfloor = floor(longmin);
                    if ((longmin-longminfloor)==0){
                        easternsecond = "0\" ";
                        easternnmintue = std::to_string(longminfloor)+"\' ";
                        double long2add1= long2;
                        if (long2<0){
                            headinglong = "W";
                            long2add1= long2*-1;
                        }
                        else{
                            headinglong = "E";
                        }
                        longadd = std::to_string(int(long2add1))+"d ";
                    }
                    else{
                        double longsec = (longmin-longminfloor) * 60.0;
                        double longsecfloor = floor(longsec);
                        easternnmintue = std::to_string(longminfloor)+"\' ";
                        easternsecond = std::to_string(longsecfloor)+"\" ";
                        double long2add1= long2;
                        if (long2<0){
                            headinglong = "W";
                            long2add1= long2*-1;
                        }
                        else{
                            headinglong = "E";
                        }
                        longadd = std::to_string(int(long2add1))+"d ";
                    }
                }
                descript = "Walk "+walking+"to "+ latadd+ northmintue+northsecond+headinglat+ longadd+easternnmintue+easternsecond+headinglong;
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                desc.push_back(descript);
                std::cout<<"@ line: "<<__LINE__<<std::endl;
                descript = "";
            }
            std::cout<<"@ line: "<<__LINE__<<std::endl;
        }
        std::cout<<"@ line: "<<__LINE__<<std::endl;
    }
    double lat2 = Nodes[NodeTranslation.find(std::get<1>(path.back()))->second].TLat;
    double long2 = Nodes[NodeTranslation.find(std::get<1>(path.back()))->second].TLong;
    double lat1 = Nodes[NodeTranslation.find(std::get<1>(path[1]))->second].TLat;
    double long1 = Nodes[NodeTranslation.find(std::get<1>(path[1]))->second].TLong;
    long flooredlat = floor(lat1);
    long flooredlong = floor(long1);
    long flooredlat2 = floor(lat2);
    long flooredlong2 = floor(long2);
    std::string walking;
    std::string headinglat;
    std::string headinglong;
    std::string northmintue;
    std::string easternnmintue;
    std::string latadd;
    std::string longadd;
    std::string easternsecond;
    std::string northsecond;

    if (lat2-flooredlat2 ==0) {
        northmintue = "0\' ";
        northsecond = "0\" ";
        double lat2add1;
        if (lat2 < 0){
            headinglat = "S, ";
            lat2add1= lat2*-1;
        }
        else{
            lat2add1= lat2;
            headinglat = "N, ";
        }
        latadd = std::to_string(int(lat2add1))+"d ";
    }
    else{
        double latmin = (lat2-flooredlat2) * 60.0;
        double latminfloor = floor(latmin);
        if ((latmin-latminfloor)==0){
            northsecond = "0\" ";
            northmintue = std::to_string(int(latminfloor))+"\' ";
            double lat2add1= lat2*-1;
            if (lat2 < 0){
                headinglat = "S, ";
                lat2add1= lat2*-1;
            }
            else{
                lat2add1= lat2;
                headinglat = "N, ";
            }
            latadd = std::to_string(int(lat2add1))+"d ";
        }
        else{
            double latsec = (latmin-latminfloor) * 60.0;
            double latsecfloor = floor(latsec);
            northmintue = std::to_string(latminfloor)+"\' ";
            northsecond = std::to_string(latsecfloor)+"\" ";
            double lat2add1;
            if (lat2 < 0){
                headinglat = "S, ";
                lat2add1= lat2*-1;
            }
            else{
                lat2add1= lat2*-1;
                headinglat = "N, ";
            }
            latadd = std::to_string(int(lat2add1))+"d ";
        }
    }
    if (long2-flooredlong2 ==0) {
        easternnmintue = "0\' ";
        easternsecond = "0\" ";
        double long2add1= long2;
        if (long2<0){
            headinglong = "W";
            long2add1= long2*-1;
        }
        else{
            headinglong = "E";
        }
        longadd = std::to_string(int(long2add1))+"d ";
    }
    else{
        double longmin = (long2-flooredlong2) * 60.0;
        double longminfloor = floor(longmin);
        if ((longmin-longminfloor)==0){
            easternsecond = "0\" ";
            easternnmintue = std::to_string(longminfloor)+"\' ";
            double long2add1= long2;
            if (long2<0){
                headinglong = "W";
                long2add1= long2*-1;
            }
            else{
                headinglong = "E";
            }
            longadd = std::to_string(int(long2add1))+"d ";
        }
        else{
            double longsec = (longmin-longminfloor) * 60.0;
            double longsecfloor = floor(longsec);
            easternnmintue = std::to_string(longminfloor)+"\' ";
            easternsecond = std::to_string(longsecfloor)+"\" ";
            double long2add1= long2;
            if (long2<0){
                headinglong = "W";
                long2add1= long2*-1;
            }
            else{
                headinglong = "E";
            }
            longadd = std::to_string(int(long2add1))+"d ";
        }
    }
    descript = "End at "+ latadd+ northmintue+northsecond+headinglat+ longadd+easternnmintue+easternsecond+headinglong;
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    desc.push_back(descript);
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    descript = "";
    std::cout<<"@ line: "<<__LINE__<<std::endl;
    return true;
}
