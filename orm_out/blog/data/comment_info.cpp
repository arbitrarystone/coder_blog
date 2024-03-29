#include "comment_info.hpp"
#include "src/log.hpp"

namespace blog {
namespace data {

static stone::Logger::ptr g_logger = STONE_LOG_NAME("orm");

CommentInfo::CommentInfo()
    :m_state()
    ,m_isDeleted()
    ,m_cId()
    ,m_userId()
    ,m_articleId()
    ,m_parentId()
    ,m_praise()
    ,m_content()
    ,m_createTime() {
}

std::string CommentInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["c_id"] = std::to_string(m_cId);
    jvalue["user_id"] = std::to_string(m_userId);
    jvalue["article_id"] = std::to_string(m_articleId);
    jvalue["content"] = m_content;
    jvalue["parent_id"] = std::to_string(m_parentId);
    jvalue["state"] = m_state;
    jvalue["is_deleted"] = m_isDeleted;
    jvalue["praise"] = std::to_string(m_praise);
    jvalue["create_time"] = stone::Time2Str(m_createTime);
    return stone::JsonUtil::ToString(jvalue);
}

void CommentInfo::setCId(const int64_t& v) {
    m_cId = v;
}

void CommentInfo::setUserId(const int64_t& v) {
    m_userId = v;
}

void CommentInfo::setArticleId(const int64_t& v) {
    m_articleId = v;
}

void CommentInfo::setContent(const std::string& v) {
    m_content = v;
}

void CommentInfo::setParentId(const int64_t& v) {
    m_parentId = v;
}

void CommentInfo::setState(const int32_t& v) {
    m_state = v;
}

void CommentInfo::setIsDeleted(const int32_t& v) {
    m_isDeleted = v;
}

void CommentInfo::setPraise(const int64_t& v) {
    m_praise = v;
}

void CommentInfo::setCreateTime(const int64_t& v) {
    m_createTime = v;
}


int CommentInfoDao::Update(CommentInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "update comment set user_id = ?, article_id = ?, content = ?, parent_id = ?, state = ?, is_deleted = ?, praise = ?, create_time = ? where c_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_userId);
    stmt->bindInt64(2, info->m_articleId);
    stmt->bindString(3, info->m_content);
    stmt->bindInt64(4, info->m_parentId);
    stmt->bindInt32(5, info->m_state);
    stmt->bindInt32(6, info->m_isDeleted);
    stmt->bindInt64(7, info->m_praise);
    stmt->bindTime(8, info->m_createTime);
    stmt->bindInt64(9, info->m_cId);
    return stmt->execute();
}

int CommentInfoDao::Insert(CommentInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "insert into comment (user_id, article_id, content, parent_id, state, is_deleted, praise, create_time) values (?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_userId);
    stmt->bindInt64(2, info->m_articleId);
    stmt->bindString(3, info->m_content);
    stmt->bindInt64(4, info->m_parentId);
    stmt->bindInt32(5, info->m_state);
    stmt->bindInt32(6, info->m_isDeleted);
    stmt->bindInt64(7, info->m_praise);
    stmt->bindTime(8, info->m_createTime);
    int rt = stmt->execute();
    if(rt == 0) {
        info->m_cId = conn->getLastInsertId();
    }
    return rt;
}

int CommentInfoDao::InsertOrUpdate(CommentInfo::ptr info, stone::IDB::ptr conn) {
    if(info->m_cId == 0) {
        return Insert(info, conn);
    }
    std::string sql = "replace into comment (c_id, user_id, article_id, content, parent_id, state, is_deleted, praise, create_time) values (?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_cId);
    stmt->bindInt64(2, info->m_userId);
    stmt->bindInt64(3, info->m_articleId);
    stmt->bindString(4, info->m_content);
    stmt->bindInt64(5, info->m_parentId);
    stmt->bindInt32(6, info->m_state);
    stmt->bindInt32(7, info->m_isDeleted);
    stmt->bindInt64(8, info->m_praise);
    stmt->bindTime(9, info->m_createTime);
    return stmt->execute();
}

int CommentInfoDao::Delete(CommentInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "delete from comment where c_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_cId);
    return stmt->execute();
}

int CommentInfoDao::DeleteByCId( const int64_t& c_id, stone::IDB::ptr conn) {
    std::string sql = "delete from comment where c_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, c_id);
    return stmt->execute();
}

int CommentInfoDao::DeleteByUserId( const int64_t& user_id, stone::IDB::ptr conn) {
    std::string sql = "delete from comment where user_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, user_id);
    return stmt->execute();
}

int CommentInfoDao::DeleteByArticleId( const int64_t& article_id, stone::IDB::ptr conn) {
    std::string sql = "delete from comment where article_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, article_id);
    return stmt->execute();
}

int CommentInfoDao::QueryAll(std::vector<CommentInfo::ptr>& results, stone::IDB::ptr conn) {
    std::string sql = "select c_id, user_id, article_id, content, parent_id, state, is_deleted, praise, create_time from comment";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    auto rt = stmt->query();
    if(!rt) {
        return stmt->getErrno();
    }
    while (rt->next()) {
        CommentInfo::ptr v(new CommentInfo);
        v->m_cId = rt->getInt64(0);
        v->m_userId = rt->getInt64(1);
        v->m_articleId = rt->getInt64(2);
        v->m_content = rt->getString(3);
        v->m_parentId = rt->getInt64(4);
        v->m_state = rt->getInt32(5);
        v->m_isDeleted = rt->getInt32(6);
        v->m_praise = rt->getInt64(7);
        v->m_createTime = rt->getTime(8);
        results.push_back(v);
    }
    return 0;
}

CommentInfo::ptr CommentInfoDao::Query( const int64_t& c_id, stone::IDB::ptr conn) {
    std::string sql = "select c_id, user_id, article_id, content, parent_id, state, is_deleted, praise, create_time from comment where c_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return nullptr;
    }
    stmt->bindInt64(1, c_id);
    auto rt = stmt->query();
    if(!rt) {
        return nullptr;
    }
    if(!rt->next()) {
        return nullptr;
    }
    CommentInfo::ptr v(new CommentInfo);
    v->m_cId = rt->getInt64(0);
    v->m_userId = rt->getInt64(1);
    v->m_articleId = rt->getInt64(2);
    v->m_content = rt->getString(3);
    v->m_parentId = rt->getInt64(4);
    v->m_state = rt->getInt32(5);
    v->m_isDeleted = rt->getInt32(6);
    v->m_praise = rt->getInt64(7);
    v->m_createTime = rt->getTime(8);
    return v;
}

int CommentInfoDao::QueryByUserId(std::vector<CommentInfo::ptr>& results,  const int64_t& user_id, stone::IDB::ptr conn) {
    std::string sql = "select c_id, user_id, article_id, content, parent_id, state, is_deleted, praise, create_time from comment where user_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, user_id);
    auto rt = stmt->query();
    if(!rt) {
        return 0;
    }
    while (rt->next()) {
        CommentInfo::ptr v(new CommentInfo);
        v->m_cId = rt->getInt64(0);
        v->m_userId = rt->getInt64(1);
        v->m_articleId = rt->getInt64(2);
        v->m_content = rt->getString(3);
        v->m_parentId = rt->getInt64(4);
        v->m_state = rt->getInt32(5);
        v->m_isDeleted = rt->getInt32(6);
        v->m_praise = rt->getInt64(7);
        v->m_createTime = rt->getTime(8);
        results.push_back(v);
    };
    return 0;
}

int CommentInfoDao::QueryByArticleId(std::vector<CommentInfo::ptr>& results,  const int64_t& article_id, stone::IDB::ptr conn) {
    std::string sql = "select c_id, user_id, article_id, content, parent_id, state, is_deleted, praise, create_time from comment where article_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, article_id);
    auto rt = stmt->query();
    if(!rt) {
        return 0;
    }
    while (rt->next()) {
        CommentInfo::ptr v(new CommentInfo);
        v->m_cId = rt->getInt64(0);
        v->m_userId = rt->getInt64(1);
        v->m_articleId = rt->getInt64(2);
        v->m_content = rt->getString(3);
        v->m_parentId = rt->getInt64(4);
        v->m_state = rt->getInt32(5);
        v->m_isDeleted = rt->getInt32(6);
        v->m_praise = rt->getInt64(7);
        v->m_createTime = rt->getTime(8);
        results.push_back(v);
    };
    return 0;
}

int CommentInfoDao::CreateTableSQLite3(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE comment("
            "c_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "user_id INTEGER NOT NULL DEFAULT 0,"
            "article_id INTEGER NOT NULL DEFAULT 0,"
            "content TEXT NOT NULL DEFAULT '',"
            "parent_id INTEGER NOT NULL DEFAULT 0,"
            "state INTEGER NOT NULL DEFAULT 0,"
            "is_deleted INTEGER NOT NULL DEFAULT 0,"
            "praise INTEGER NOT NULL DEFAULT 0,"
            "create_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00');"
            "CREATE INDEX comment_user_id ON comment(user_id);"
            "CREATE INDEX comment_article_id ON comment(article_id);"
            );
}

int CommentInfoDao::CreateTableMySQL(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE comment("
            "`c_id` bigint AUTO_INCREMENT COMMENT '评论id',"
            "`user_id` bigint NOT NULL DEFAULT 0 COMMENT '用户id',"
            "`article_id` bigint NOT NULL DEFAULT 0 COMMENT '文章id',"
            "`content` varchar(4096) NOT NULL DEFAULT '' COMMENT '内容',"
            "`parent_id` bigint NOT NULL DEFAULT 0 COMMENT '父评论id',"
            "`state` int NOT NULL DEFAULT 0 COMMENT '状态1审核中2已发布',"
            "`is_deleted` int NOT NULL DEFAULT 0 COMMENT '是否删除',"
            "`praise` bigint NOT NULL DEFAULT 0 COMMENT '点赞数',"
            "`create_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '创建时间',"
            "PRIMARY KEY(`c_id`),"
            "KEY `comment_user_id` (`user_id`),"
            "KEY `comment_article_id` (`article_id`)) COMMENT='评论表'");
}
} //namespace data
} //namespace blog
