echo Decrtypting id_rsa...
openssl aes-256-cbc -K $encrypted_2fc69c4133c3_key -iv $encrypted_2fc69c4133c3_iv -in travis/id_rsa.enc -out travis/id_rsa -d || exit 1
eval "$(ssh-agent -s)"
chmod 600 travis/id_rsa
ssh-add travis/id_rsa || exit 1

SSHOPTS="ssh -o StrictHostKeyChecking=no"

case "$TRAVIS_OS_NAME" in
    windows)
        echo Uploading windows artifacts...
        rsync -e "$SSHOPTS" ddb-xdispatch-win-latest.zip waker,deadbeef@frs.sourceforge.net:/home/frs/project/d/de/deadbeef/staticdeps/ || exit 1
        taskkill //IM ssh-agent.exe //F
    ;;
esac
