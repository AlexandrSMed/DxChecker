function(get_sign_params description descriptionURL pfxPath pfxPassphrase)
    if (SIGN_PARAMS)
        return()
    else()
        set(SIGN_PARAMS
            /f ${pfxPath} /p ${pfxPassphrase}
            /t http://timestamp.digicert.com
            /d ${description} /du ${descriptionURL}
            PARENT_SCOPE)
    endif()
endfunction()

function(code_sign_windows target description descriptionURL pfxPath pfxPassphrase)
    find_package(signtool REQUIRED)
    if (signtool_EXECUTABLE)
        get_sign_params(${description} ${descriptionURL} ${pfxPath} ${pfxPassphrase})
        add_custom_command(TARGET ${target} POST_BUILD
                           COMMAND ${signtool_EXECUTABLE} sign ${SIGN_PARAMS} $<TARGET_FILE:${target}>
                           VERBATIM)
    else()
        message(SEND_ERROR "Failed to set up code signing command. Could not locate signtool executable")
    endif()
endfunction()