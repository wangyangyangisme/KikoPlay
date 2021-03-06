#ifndef ANIMEMODEL_H
#define ANIMEMODEL_H
#include <QAbstractItemModel>
#include "animeinfo.h"
class AnimeLibrary;
class AnimeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit AnimeModel(AnimeLibrary *library = nullptr);
public:
    void setActive(bool isActive);
    void deleteAnime(const QModelIndex &index);
    Anime *getAnime(const QModelIndex &index, bool fillInfo);
signals:
    void animeMessage(const QString &msg, int flags, bool hasMore);
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const{return parent.isValid()?QModelIndex():createIndex(row,column);}
    virtual QModelIndex parent(const QModelIndex &) const{return QModelIndex();}
    virtual int rowCount(const QModelIndex &parent) const {return parent.isValid()?0:animes.count();}
    virtual int columnCount(const QModelIndex &parent) const {return parent.isValid()?0:1;}
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual void fetchMore(const QModelIndex &);
    inline virtual bool canFetchMore(const QModelIndex &) const{ return hasMoreAnimes; }
private:
    const int limitCount=200;
    int currentOffset;
    QList<Anime *> animes, tmpAnimes;
    bool active;
    bool hasMoreAnimes;
    void addAnime(Anime *anime);
    void removeAnime(Anime *anime);
    void showStatisMessage();
};

#endif // ANIMEMODEL_H
