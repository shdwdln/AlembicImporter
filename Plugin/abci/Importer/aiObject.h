#pragma once
class aiContext;
class aiSchemaBase;
class aiXForm;
class aiPolyMesh;
class aiCamera;

class aiObject
{
public:
    aiObject();
    aiObject(aiContext *ctx, aiObject *parent, const abcObject &abc);
    ~aiObject();

    const char* getName() const;
    const char* getFullName() const;
    uint32_t    getNumChildren() const;
    aiObject*   getChild(int i);
    aiObject*   getParent() const;
    void        cacheSamples(int64_t startIndex, int64_t endIndex);
    void        readConfig();
    void        updateSample(const abcSampleSelector& ss);
 
    aiXForm*    getXForm() const;
    aiPolyMesh* getPolyMesh() const;
    aiCamera*   getCamera() const;
    aiPoints*   getPoints() const;

    template<class F>
    void eachChildren(const F &f)
    {
        for (auto *c : m_children) { f(c); }
    }

    template<class F>
    void eachChildrenRecursive(const F &f)
    {
        for (auto *c : m_children) {
            f(c);
            c->eachChildrenRecursive(f);
        }
    }

public:
    // for internal use
    aiContext*  getContext() const;
    abcObject&  getAbcObject();
    aiObject*   newChild(const abcObject &abc);
    void        removeChild(aiObject *c);

private:
    aiContext   *m_ctx = nullptr;
    abcObject   m_abc;
    aiObject    *m_parent = nullptr;
    std::vector<aiObject*> m_children;

    std::vector<aiSchemaBase*>  m_schemas;
    std::unique_ptr<aiXForm>    m_xform;
    std::unique_ptr<aiPolyMesh> m_polymesh;
    std::unique_ptr<aiCamera>   m_camera;
    std::unique_ptr<aiPoints>   m_points;
};
